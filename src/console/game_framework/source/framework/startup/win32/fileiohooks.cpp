#include "precomp.h"
#include "fileiohooks.h"

#include <hash_map>

#include "framework/core/macros/debugmacros.h"

PFN_CreateFileA g_pfnCreateFileA = CreateFileA;                         // 0x0060D818
PFN_ReadFile g_pfnReadFile = ReadFile;                                  // 0x0060D81C
PFN_ReadFileEx g_pfnReadFileEx = ReadFileEx;                            // 0x0060D820
PFN_WriteFile g_pfnWriteFile = WriteFile;                               // 0x0060D824
PFN_GetOverlappedResult g_pfnGetOverlappedResult = GetOverlappedResult; // 0x0062F1D8
PFN_CancelIo g_pfnCancelIo = CancelIo;                                  // 0x0062F180
PFN_CloseHandle g_pfnCloseHandle = CloseHandle;                         // 0x0062F1DC

enum EFileIOState
{
   FILEIO_READ = 0,      // queued read, serviced by the worker
   FILEIO_WRITE = 1,     // queued write, serviced by the worker
   FILEIO_CANCELLED = 2, // set by EmuCancelIo
   FILEIO_COMPLETE = 3,
   FILEIO_EOF = 4
};

// An overlapped read/write queued by the emulation layer (0x1C bytes)
struct FileIORequest
{
   HANDLE hFile;
   LPVOID pBuffer;
   BYTE *pCursor;
   LPOVERLAPPED pOverlapped;
   int eState; // EFileIOState
   DWORD dwDone;
   DWORD dwTotal;
};

typedef stdext::hash_map<HANDLE, bool> FileHandleMap;         // handle -> opened with FILE_FLAG_OVERLAPPED
typedef stdext::hash_map<DWORD, FileIORequest *> FileIORequestMap; // OVERLAPPED::InternalHigh -> request

namespace
{
   bool g_bFileIOThreadRunning = true;            // 0x0060D80C
   int g_nFileIOChunkSize = 0x2000;               // 0x0060D810
   DWORD g_dwFileIOSleepMs = 1;                   // 0x0060D814
   HANDLE g_hFileIOMutex = NULL;                  // 0x0062F174
   HANDLE g_hFileIOThread = NULL;                 // 0x0062F178
   DWORD g_dwNextFileIORequestId = 0;             // 0x0062F17C
   FileHandleMap g_FileHandles;                   // 0x0062F184
   FileIORequestMap g_FileIORequests;             // 0x0062F1B0
   FileIORequestMap::iterator g_itFileIORequest;  // 0x0062F1AC

   void LockFileIO()
   {
      WaitForSingleObject(g_hFileIOMutex, INFINITE);
   }

   void UnlockFileIO()
   {
      ReleaseMutex(g_hFileIOMutex);
   }

   // Erase (and free) every request matching hFile, or matching the request id when hFile is NULL.
   // Caller holds the lock.
   void RemoveFileIORequests(HANDLE hFile, DWORD dwRequestId)
   {
      FileIORequestMap::iterator it = g_FileIORequests.begin();
      while (it != g_FileIORequests.end())
      {
         FileIORequestMap::iterator itNext = it;
         ++itNext;

         FileIORequest *pRequest = it->second;
         bool bMatch = (hFile != NULL) ? (pRequest->hFile == hFile)
                                       : ((DWORD)pRequest->pOverlapped->InternalHigh == dwRequestId);
         if (bMatch)
         {
            if (it == g_itFileIORequest)
            {
               g_itFileIORequest = itNext;
            }
            g_FileIORequests.erase(it);
            delete pRequest;
         }

         it = itNext;
      }
   }

   // Shared by EmuReadFile / EmuReadFileEx / EmuWriteFile for handles opened as overlapped
   BOOL QueueFileIORequest(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytes, LPOVERLAPPED lpOverlapped,
                           int eState)
   {
      lpOverlapped->Internal = STATUS_PENDING;
      lpOverlapped->InternalHigh = g_dwNextFileIORequestId++;

      FileIORequest *pRequest = new FileIORequest;
      pRequest->hFile = hFile;
      pRequest->pBuffer = (LPVOID)lpBuffer;
      pRequest->pCursor = (BYTE *)lpBuffer;
      pRequest->pOverlapped = lpOverlapped;
      pRequest->eState = eState;
      pRequest->dwDone = 0;
      pRequest->dwTotal = nNumberOfBytes;

      LockFileIO();
      g_FileIORequests.insert(FileIORequestMap::value_type((DWORD)lpOverlapped->InternalHigh, pRequest));
      UnlockFileIO();

      SetLastError(ERROR_IO_PENDING);
      return FALSE;
   }

   // The original reads it->second without checking for end(); an unknown handle is treated as
   // non-overlapped here instead.
   bool IsOverlappedHandle(HANDLE hFile)
   {
      LockFileIO();
      FileHandleMap::iterator it = g_FileHandles.find(hFile);
      bool bOverlapped = (it != g_FileHandles.end()) && it->second;
      UnlockFileIO();
      return bOverlapped;
   }

   HANDLE WINAPI EmuCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                                DWORD dwFlagsAndAttributes, HANDLE /* hTemplateFile */)
   {
      bool bOverlapped = (dwFlagsAndAttributes & FILE_FLAG_OVERLAPPED) != 0;
      if (bOverlapped)
      {
         dwFlagsAndAttributes &= ~(FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING);
      }

      HANDLE hFile = CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                                 dwCreationDisposition, dwFlagsAndAttributes, NULL);
      if (hFile == INVALID_HANDLE_VALUE)
      {
         return INVALID_HANDLE_VALUE;
      }

      SetLastError(ERROR_IO_PENDING);
      LockFileIO();
      g_FileHandles.insert(FileHandleMap::value_type(hFile, bOverlapped));
      UnlockFileIO();
      return hFile;
   }

   BOOL WINAPI EmuReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                           LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
   {
      if (!IsOverlappedHandle(hFile))
      {
         if (lpOverlapped != NULL)
         {
            SetFilePointer(hFile, lpOverlapped->Offset, NULL, FILE_BEGIN);
         }
         return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, NULL);
      }

      if (lpNumberOfBytesRead != NULL)
      {
         *lpNumberOfBytesRead = 0;
      }
      return QueueFileIORequest(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, FILEIO_READ);
   }

   // The completion routine is never called; callers poll with GetOverlappedResult.
   BOOL WINAPI EmuReadFileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                             LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE /* lpCompletionRoutine */)
   {
      if (!IsOverlappedHandle(hFile))
      {
         DWORD dwBytesRead;
         if (lpOverlapped != NULL)
         {
            SetFilePointer(hFile, lpOverlapped->Offset, NULL, FILE_BEGIN);
         }
         return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, &dwBytesRead, NULL);
      }

      return QueueFileIORequest(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, FILEIO_READ);
   }

   BOOL WINAPI EmuWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                            LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
   {
      if (!IsOverlappedHandle(hFile))
      {
         if (lpOverlapped != NULL)
         {
            SetFilePointer(hFile, lpOverlapped->Offset, NULL, FILE_BEGIN);
         }
         return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, NULL);
      }

      if (lpNumberOfBytesWritten != NULL)
      {
         *lpNumberOfBytesWritten = 0;
      }
      return QueueFileIORequest(hFile, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, FILEIO_WRITE);
   }

   BOOL WINAPI EmuGetOverlappedResult(HANDLE /* hFile */, LPOVERLAPPED lpOverlapped,
                                      LPDWORD lpNumberOfBytesTransferred, BOOL bWait)
   {
      DWORD dwRequestId = (DWORD)lpOverlapped->InternalHigh;

      LockFileIO();
      FileIORequestMap::iterator it = g_FileIORequests.find(dwRequestId);
      UnlockFileIO();
      if (it == g_FileIORequests.end())
      {
         SetLastError(ERROR_INVALID_HANDLE);
         return FALSE;
      }

      if (bWait)
      {
         for (;;)
         {
            LockFileIO();
            it = g_FileIORequests.find(dwRequestId);
            UnlockFileIO();
            if (it == g_FileIORequests.end())
            {
               SetLastError(ERROR_INVALID_HANDLE);
               return FALSE;
            }
            if (it->second->eState > FILEIO_WRITE)
            {
               break;
            }
            Sleep(5);
         }
      }

      FileIORequest *pRequest = it->second;
      if (lpNumberOfBytesTransferred != NULL)
      {
         *lpNumberOfBytesTransferred = pRequest->dwDone;
      }

      if (pRequest->eState == FILEIO_EOF)
      {
         SetLastError(ERROR_HANDLE_EOF);
         return FALSE;
      }
      if (pRequest->eState != FILEIO_COMPLETE)
      {
         SetLastError(ERROR_IO_INCOMPLETE);
         return FALSE;
      }

      LockFileIO();
      RemoveFileIORequests(NULL, dwRequestId);
      UnlockFileIO();
      return TRUE;
   }

   BOOL WINAPI EmuCancelIo(HANDLE hFile)
   {
      LockFileIO();
      for (FileIORequestMap::iterator it = g_FileIORequests.begin(); it != g_FileIORequests.end(); ++it)
      {
         if (it->second->hFile == hFile)
         {
            it->second->eState = FILEIO_CANCELLED;
         }
      }
      UnlockFileIO();
      return TRUE;
   }

   BOOL WINAPI EmuCloseHandle(HANDLE hObject)
   {
      LockFileIO();
      FileHandleMap::iterator it = g_FileHandles.find(hObject);
      if (it != g_FileHandles.end())
      {
         g_FileHandles.erase(it);
      }
      UnlockFileIO();

      LockFileIO();
      RemoveFileIORequests(hObject, 0);
      UnlockFileIO();

      return CloseHandle(hObject);
   }

   // Services one chunk of the current request per pass, then moves on once it is no longer pending.
   DWORD WINAPI FileIOThreadProc(LPVOID /* lpParameter */)
   {
      while (g_bFileIOThreadRunning)
      {
         LockFileIO();

         bool bMoved = false;
         if (g_itFileIORequest == g_FileIORequests.end())
         {
            g_itFileIORequest = g_FileIORequests.begin();
            bMoved = true;
         }
         else
         {
            FileIORequest *pRequest = g_itFileIORequest->second;
            if (pRequest->eState == FILEIO_READ || pRequest->eState == FILEIO_WRITE)
            {
               DWORD dwTransferred = 0;
               DWORD dwToTransfer = pRequest->dwTotal - pRequest->dwDone;
               if (g_nFileIOChunkSize < (int)dwToTransfer)
               {
                  dwToTransfer = g_nFileIOChunkSize;
               }

               BOOL bOk;
               if (pRequest->eState == FILEIO_READ)
               {
                  bOk = ReadFile(pRequest->hFile, pRequest->pCursor, dwToTransfer, &dwTransferred, NULL);
               }
               else
               {
                  bOk = WriteFile(pRequest->hFile, pRequest->pCursor, dwToTransfer, &dwTransferred, NULL);
               }

               pRequest->dwDone += dwTransferred;
               pRequest->pCursor += dwTransferred;
               GetLastError();

               if (!bOk)
               {
                  pRequest->eState = (GetLastError() == ERROR_HANDLE_EOF) ? FILEIO_EOF : FILEIO_COMPLETE;
                  pRequest->pOverlapped->Internal = 0;
               }
               else if (pRequest->dwDone >= pRequest->dwTotal || dwTransferred == 0)
               {
                  pRequest->eState = FILEIO_COMPLETE;
                  pRequest->pOverlapped->Internal = 0;
               }
            }
            else
            {
               ++g_itFileIORequest;
               bMoved = true;
            }
         }

         // Seek once when a pending request becomes current
         if (bMoved && g_itFileIORequest != g_FileIORequests.end())
         {
            FileIORequest *pRequest = g_itFileIORequest->second;
            if (pRequest->eState == FILEIO_READ || pRequest->eState == FILEIO_WRITE)
            {
               SetFilePointer(pRequest->hFile, pRequest->pOverlapped->Offset, NULL, FILE_BEGIN);
            }
         }

         UnlockFileIO();
         Sleep(g_dwFileIOSleepMs);
      }

      return 0;
   }
}

void InstallFileIOHooks(const FileIOThreadParams *pParams)
{
   RWS_FUNCTION("InstallFileIOHooks");

   OSVERSIONINFOA osvi;
   memset(&osvi, 0, sizeof(osvi));
   osvi.dwOSVersionInfoSize = sizeof(osvi);

#pragma warning(push)
#pragma warning(disable : 4996) // GetVersionExA is deprecated in current SDKs
   BOOL bGotVersion = GetVersionExA(&osvi);
#pragma warning(pop)

   // Windows 2000 and later handle overlapped file I/O natively
   if (bGotVersion && osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion >= 5)
   {
      g_pfnCreateFileA = CreateFileA;
      g_pfnReadFile = ReadFile;
      g_pfnReadFileEx = ReadFileEx;
      g_pfnWriteFile = WriteFile;
      g_pfnGetOverlappedResult = GetOverlappedResult;
      g_pfnCancelIo = CancelIo;
      g_pfnCloseHandle = CloseHandle;
   }
   else
   {
      g_pfnCreateFileA = EmuCreateFileA;
      g_pfnReadFile = EmuReadFile;
      g_pfnReadFileEx = EmuReadFileEx;
      g_pfnWriteFile = EmuWriteFile;
      g_pfnGetOverlappedResult = EmuGetOverlappedResult;
      g_pfnCancelIo = EmuCancelIo;
      g_pfnCloseHandle = EmuCloseHandle;

      g_hFileIOMutex = CreateMutexA(NULL, FALSE, NULL);
      g_itFileIORequest = g_FileIORequests.begin();

      DWORD dwThreadId = 0;
      g_hFileIOThread = CreateThread(NULL, 0, FileIOThreadProc, NULL, CREATE_SUSPENDED, &dwThreadId);
      if (pParams != NULL)
      {
         SetThreadPriority(g_hFileIOThread, pParams->nThreadPriority);
         g_nFileIOChunkSize = (int)pParams->fChunkSize;
         g_dwFileIOSleepMs = pParams->dwSleepMs;
      }
      else
      {
         SetThreadPriority(g_hFileIOThread, THREAD_PRIORITY_NORMAL);
      }
      ResumeThread(g_hFileIOThread);
   }

   RWS_RETURNVOID();
}

void RestoreFileIOHooks()
{
   RWS_FUNCTION("RestoreFileIOHooks");

   g_bFileIOThreadRunning = false;
   if (g_hFileIOThread != NULL)
   {
      CloseHandle(g_hFileIOThread);
      CloseHandle(g_hFileIOMutex);
      g_hFileIOThread = NULL;
      g_hFileIOMutex = NULL;
   }

   g_pfnCloseHandle = CloseHandle;
   g_pfnCreateFileA = CreateFileA;
   g_pfnReadFile = ReadFile;
   g_pfnReadFileEx = ReadFileEx;
   g_pfnWriteFile = WriteFile;
   g_pfnGetOverlappedResult = GetOverlappedResult;
   g_pfnCancelIo = CancelIo;

   RWS_RETURNVOID();
}
