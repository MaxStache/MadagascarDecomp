#ifndef FILEIOHOOKS_H
#define FILEIOHOOKS_H

#include <windows.h>

// Win32 file API used by the streaming code. Points at the real API on Windows 2000 and later,
// at the overlapped-I/O emulation in fileiohooks.cpp on older systems.
typedef HANDLE(WINAPI *PFN_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL(WINAPI *PFN_ReadFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL(WINAPI *PFN_ReadFileEx)(HANDLE, LPVOID, DWORD, LPOVERLAPPED, LPOVERLAPPED_COMPLETION_ROUTINE);
typedef BOOL(WINAPI *PFN_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL(WINAPI *PFN_GetOverlappedResult)(HANDLE, LPOVERLAPPED, LPDWORD, BOOL);
typedef BOOL(WINAPI *PFN_CancelIo)(HANDLE);
typedef BOOL(WINAPI *PFN_CloseHandle)(HANDLE);

extern PFN_CreateFileA g_pfnCreateFileA;
extern PFN_ReadFile g_pfnReadFile;
extern PFN_ReadFileEx g_pfnReadFileEx;
extern PFN_WriteFile g_pfnWriteFile;
extern PFN_GetOverlappedResult g_pfnGetOverlappedResult;
extern PFN_CancelIo g_pfnCancelIo;
extern PFN_CloseHandle g_pfnCloseHandle;

struct FileIOThreadParams
{
   int nThreadPriority;
   float fChunkSize; // max bytes the worker reads/writes per step
   DWORD dwSleepMs;  // pause between worker steps
};

void InstallFileIOHooks(const FileIOThreadParams *pParams);
void RestoreFileIOHooks();

#endif // FILEIOHOOKS_H
