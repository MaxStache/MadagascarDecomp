/*****************************************************************************
 *
 * File :     Win.cpp
 *
 * Abstract : This file contains the starup/shutdown code specific to windows.
 *
 *****************************************************************************
 *
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd. or
 * Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. will not, under any
 * circumstances, be liable for any lost revenue or other damages arising
 * from the use of this file.
 *
 * Copyright (c) 2000 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 *****************************************************************************/
#include "precomp.h"

// #define RWS_CALLSTACKENABLE
// #define RWS_TRACEENABLE

//////////////////////////////////////////////////////////////////
//
// System Includes
//
#include "win.h"
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <direct.h>

using namespace std;

#include "rwreg.h"

using namespace CSL;

//////////////////////////////////////////////////////////////////
//
// RenderWare Studio Includes
//
#include <rwcore.h>
#include "rtfsyst.h" // New 3.6 File System

#include "../startup.h"
#include "framework/mainloop/mainloop.h"
#include "framework/mainloop/render.h"
#include "../loadgamedatabase.h"
#include "framework/core/macros/debugmacros.h"
#include "framework/toolkits/world/clevel.h"
#include "framework/toolkits/world/helpers/camerahelper.h"
#include "framework/mainloop/logic.h"

namespace
{
   using namespace RWS;

   // Data/constants
#if (defined(D3D8_DRVMODEL_H))
   const TCHAR kMainWindowClassName[] = _T("RWSConsoleD3D8");
   const TCHAR kMainWindowName[] = _T("RWS Console (DirectX8)");
#elif (defined(D3D9_DRVMODEL_H))
   const TCHAR kMainWindowClassName[] = _T("RWSConsoleD3D9");
   const TCHAR kMainWindowName[] = _T("RWS Console (DirectX9)");
#else
   const TCHAR kMainWindowClassName[] = _T("RWSConsoleOpenGL");
   const TCHAR kMainWindowName[] = _T("RWS Console (OpenGL)");
#endif

   // Location of window params in registry
   const char *kRegGroup = "GameFrameWork";
   const char *kRegName = "GameSettings";

   // This section defines the requested windows/screen
   //
   const RwUInt32 kBitDepth = 32;
   const RwUInt32 kZBitDepth = 16;

   // Globals
   HWND theMainWindow = 0;
   bool quit = false;

   bool minimized = false;

   int g_nWindowBorderX = 0;
   int g_nWindowBorderY = 0;
   int g_nWindowWidth = 800;
   int g_nWindowHeight = 600;

   bool g_bWindowedMode = false;

   // Used for new RW 3.6 FileSystem
   const RwUInt32 UNC_PATH_SIZE = 256; /* should be sufficient */
   const RwUInt32 MAX_NB_FILES_PER_FS = 20;

   int StringToInt(const string &str)
   {
      int retVal;

      istringstream iss(str);

      iss >> retVal;

      return retVal;
   }

   string IntToString(const int val)
   {
      ostringstream oss;

      oss << val;

      return oss.str();
   }

   /*
    *  Resize visible display area.
    *
    *  \param screenWidth Required width of display area.
    *  \param screenHeight Required height of display area.
    *  \param ZBufferDepth Require z buffer depth of display area.
    *
    *  \returns Returns true on success.
    */
   bool Resize(const RwUInt32 ScreenWidth,
               const RwUInt32 ScreenHeight,
               const RwUInt32 ZBufferDepth)
   {
      RWS_FUNCTION("Resize");

      if (MainLoop::Render::GetCamera())
      {
         // Check if minimized
         //
         if (ScreenWidth == 0 || ScreenHeight == 0)
         {
         }
         else
         {
            const RwV2d ViewWindow = *RwCameraGetViewWindow(MainLoop::Render::GetCamera());

            // Keep the frame
            //
            RwFrame *pOldFrame = RwCameraGetFrame(MainLoop::Render::GetCamera());
            RwCameraSetFrame(MainLoop::Render::GetCamera(), 0);

            CameraHelper::Destroy(MainLoop::Render::GetCamera());

            MainLoop::Render::SetCamera(CameraHelper::CreateMainRasterCamera(ScreenWidth,
                                                                             ScreenHeight,
                                                                             ZBufferDepth));

            // Use the old frame in the new camera
            //
            RwFrame *pNewFram = RwCameraGetFrame(MainLoop::Render::GetCamera());
            RwCameraSetFrame(MainLoop::Render::GetCamera(), pOldFrame);
            RwFrameDestroy(pNewFram);

            // Setup aspect ratio as same as old camera,
            // trick is that ViewWindow.x = (RwReal)RwTan(pCmsg->fov * 0.5f);
            //
            CameraHelper::SetFieldOfView(ViewWindow.x, MainLoop::Render::GetCamera());
         }

         CEventHandler::RegisterMsg(Win::iMsgResizeCameraRasters, Win::iMsgResizeCameraRastersStr, 0);
         // Inform any behaviors that may be using Sub-Rasters that the screen size has changed
         //
         SendMsg(RWS::Win::iMsgResizeCameraRasters);

         CEventHandler::UnRegisterMsg(Win::iMsgResizeCameraRasters);

         RWS_RETURN(true);
      }
      else
      {
         RWS_RETURN(false);
      }
   }

   /*
    *
    *  \ingroup Win
    *
    *  Win32 only: WndProc for the main window
    *
    */
   LRESULT CALLBACK MainWndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
   {
      RWS_FUNCTION("MainWndProc");

      switch (message)
      {
      case WM_ACTIVATEAPP:
         minimized = !wParam;

         RWS_RETURN(0L);
      case WM_DESTROY:
      case WM_CLOSE:
         quit = 1;
         PostQuitMessage(0);
         RWS_RETURN(0);
      case WM_PAINT:
         PAINTSTRUCT Paint;

         BeginPaint(window, &Paint);
         RWS::MainLoop::Render::Poll();
         EndPaint(window, &Paint);

         RWS_RETURN(0L);
      case WM_SIZE:
         RwRect r;

         r.x = 0;
         r.y = 0;
         r.w = LOWORD(lParam);
         r.h = HIWORD(lParam);

         Resize(r.w, r.h, kZBitDepth);

         RWS_RETURN(0L);

      default:
         RWS_RETURN(DefWindowProc(window, message, wParam, lParam));
      }

      RWS_RETURN(-1L);
   }

   /*
    *
    *  \ingroup Win
    *
    *  Win32 only: Registers a window class for the main window
    *
    */
   bool RegisterMainWindowClass(HANDLE processInstance)
   {
      RWS_FUNCTION("RegisterMainWindowClass");

      RWS_PRE(processInstance);

      WNDCLASS windowClass;

#ifdef UNDER_CE
      windowClass.style = 0;
#else
      windowClass.style = CS_BYTEALIGNWINDOW;
#endif
      windowClass.lpfnWndProc = (WNDPROC)MainWndProc;
      windowClass.cbClsExtra = 0;
      windowClass.cbWndExtra = 0;
      windowClass.hInstance = (HINSTANCE)processInstance;
      windowClass.hIcon = 0;
      windowClass.hCursor = LoadCursor(0, IDC_ARROW);
      windowClass.hbrBackground = 0;
      windowClass.lpszMenuName = 0;
      windowClass.lpszClassName = kMainWindowClassName;

      RWS_RETURN(RegisterClass(&windowClass) != 0);
   }

   /*
    *
    *  \ingroup Win
    *
    *  Win32 only: Creates the main window
    *
    */
   HWND CreateMainWindow(LPCSTR lpszClassName, LPCSTR lpszWindowName, int x, int y, int nWidth, int nHeight,
                         WNDPROC lpfnWndProc, HINSTANCE hInstance, unsigned int uIconResourceId, bool bFullScreen)
   {
      RWS_FUNCTION("CreateMainWindow");

      DWORD dwStyle;
      DWORD dwExStyle;
      int nWindowWidth;
      int nWindowHeight;
      RECT rect;
      WNDCLASSEXA wc;

      memset(&wc, 0, sizeof(WNDCLASSEXA));
      wc.lpfnWndProc = lpfnWndProc;
      wc.cbSize = sizeof(WNDCLASSEXA);
      wc.style = CS_OWNDC;
      wc.hInstance = hInstance;
      wc.lpszClassName = lpszClassName;
      if (uIconResourceId != 0)
      {
         wc.hIcon = LoadIconA(hInstance, (LPCSTR)(uIconResourceId & 0xffff));
      }
      RegisterClassExA(&wc);

      if (bFullScreen)
      {
         dwStyle = WS_POPUP;
         dwExStyle = WS_EX_TOPMOST;
         x = 0;
         y = 0;
         nWindowWidth = GetSystemMetrics(SM_CXSCREEN);
         nWindowHeight = GetSystemMetrics(SM_CYSCREEN);
      }
      else
      {
         dwStyle = WS_POPUP | WS_CAPTION | WS_SYSMENU;

         // grow the rect so the *client* area is nWidth x nHeight
         rect.left = 0;
         rect.top = 0;
         rect.right = nWidth;
         rect.bottom = nHeight;
         AdjustWindowRect(&rect, dwStyle, FALSE);

         nWindowWidth = rect.right - rect.left;
         nWindowHeight = rect.bottom - rect.top;
         g_nWindowBorderX = -rect.left; // left border width
         g_nWindowBorderY = -rect.top;  // title bar + top border height

         if (x == -1)
            x = (GetSystemMetrics(SM_CXSCREEN) - nWindowWidth) / 2;
         if (y == -1)
            y = (GetSystemMetrics(SM_CYSCREEN) - nWindowHeight) / 2;
      }

      SetLastError(0);
      theMainWindow = CreateWindowExA(
          dwExStyle, lpszClassName, lpszWindowName, dwStyle,
          x, y, nWindowWidth, nWindowHeight,
          NULL, NULL, hInstance, NULL);

      RWS_RETURN(theMainWindow);
   }

   /*
    *
    *  \ingroup Win
    *
    *  Win32 only: Main message pump
    *
    */
   int PumpMessages()
   {
      int result = 0;

      while (!quit)
      {
         MSG message;

         if (PeekMessage(&message, 0, 0U, 0U, PM_REMOVE | PM_NOYIELD))
         {
            if (message.message == WM_QUIT)
            {
               quit = true;
               result = message.wParam;
            }
            else
            {
               TranslateMessage(&message);
               DispatchMessage(&message);
            }
         }
         else
         {
            RwUInt32 startTime = GetTickCount(),
                     logicTime,
                     rateTime = (1000 / RWS::MainLoop::Logic::Rate);

            RWS::MainLoop::Poll();

            // Slightly less crude system than before. Check how much time has gone by.
            // This system does not link to V.Sync of display in any way.

            logicTime = GetTickCount() - startTime;

            if (logicTime < rateTime)
            {
               // Running too fast, so sleep for extra time.

               Sleep(rateTime - logicTime);
            }
         }
      }

      return (result);
   }
}

namespace RWS
{

   /*
    *
    *  \ingroup Win
    *
    *  platform specific method to install the file system
    *
    */
   RwBool psInstallFileSystem(void)
   {
      RwChar curDirBuffer[_MAX_PATH];
      RwUInt32 retValue;
      RtFileSystem *wfs;

      /* get the current directory */
      retValue = GetCurrentDirectory(_MAX_PATH, curDirBuffer);
      if (0 == retValue || retValue > _MAX_PATH)
      {
         return FALSE;
      }

      /* This is a unc path */
      if (curDirBuffer[1] != ':')
      {
         /* tag a \ to the end of the current directory */
         /* only fails if the buffer size is exhausted */
         rwstrcat(curDirBuffer, "\\");

         /** Setup the file system manager */
         if ((wfs = RtWinFSystemInit(MAX_NB_FILES_PER_FS, curDirBuffer, "unc")) != 0)
         {
            /* Now actually register the file system */
            if (RtFSManagerRegister(wfs) == FALSE)
            {
               return (FALSE);
            }
            else
            {
               RtFSManagerSetDefaultFileSystem(wfs);
            }
         }
         else
         {
            return (FALSE);
         }
      }
      else
      {
         RwUInt32 drivesMask;
         RwInt32 drive;
         RwChar fsName[2];

         CharUpper(curDirBuffer);

         /*
          * loop through all logical drives and register a file system for each
          * valid one.
          * Start at 2: this removes a:
          */
         drivesMask = GetLogicalDrives();

         for (drive = 2, drivesMask >>= 1; drivesMask != 0; drive++, drivesMask >>= 1)
         {
            if (drivesMask & 0x01)
            {
               RwInt32 ret;
               RwChar deviceName[4];

               deviceName[0] = drive + 'A' - 1;
               deviceName[1] = ':';
               deviceName[2] = '\\'; /* Needed for Win98 */
               deviceName[3] = '\0';

               ret = GetDriveType(deviceName);

               if (ret != DRIVE_UNKNOWN && ret != DRIVE_NO_ROOT_DIR)
               {
                  /* Fix device name */
                  deviceName[2] = '\0';

                  fsName[0] = deviceName[0];
                  fsName[1] = '\0';

                  /** Setup the file system manager */
                  if ((wfs = RtWinFSystemInit(MAX_NB_FILES_PER_FS, deviceName, fsName)) != 0)
                  {
                     /* Now actually register the file system */
                     if (RtFSManagerRegister(wfs) == FALSE)
                     {
                        return (FALSE);
                     }
                     else
                     {
                        if (deviceName[0] == curDirBuffer[0])
                        {
                           RtFSManagerSetDefaultFileSystem(wfs);
                        }
                     }
                  }
                  else
                  {
                     return (FALSE);
                  }
               }
            }
         }
      }

      return (TRUE);
   }

   namespace Win
   {
      CEventId iMsgResizeCameraRasters;

      /*
       *
       *  \ingroup Win
       *
       *  Win32 only: Retrieves a handle to the main window
       *
       */
      HWND GetMainWindow()
      {
         RWS_FUNCTION("GetMainWindow")
         RWS_RETURN(theMainWindow);
      }
   }
}

/*
 *
 *  \ingroup Win
 *
 *  Win32 only: Main entry point
 *
 */
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE /* prevInstance */,
                   LPSTR cmdLine,
                   int cmdShow)
{
   RWS_FUNCTION("WinMain");

   DEVMODEA currentDisplayMode;
   DEVMODEA newDisplayMode;

   HANDLE hMutex = CreateMutexA(NULL, FALSE, "Madagascar Running");
   DWORD err = GetLastError();

   // There already is an instance of the game open
   if (err == ERROR_ALREADY_EXISTS)
   {
      if (hMutex != INVALID_HANDLE_VALUE)
      {
         CloseHandle(hMutex);
      }
      RWS_RETURN(0); // exit
   }

   g_bWindowedMode = false;

   memset(&currentDisplayMode, 0, sizeof(DEVMODEA));
   BOOL bGotCurrentMode = EnumDisplaySettingsA((LPCSTR)0x0, 0xffffffff, &currentDisplayMode);

   if ((bGotCurrentMode != 0) &&
       ((currentDisplayMode.dmPelsWidth < (unsigned int)g_nWindowWidth ||
         (currentDisplayMode.dmPelsHeight < (unsigned int)g_nWindowHeight))))
   {
      newDisplayMode.dmPelsWidth = g_nWindowWidth;
      newDisplayMode.dmPelsHeight = g_nWindowHeight;
      newDisplayMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
      newDisplayMode.dmSize = sizeof(DEVMODEA);
      LONG bDisplayChangeSuccessful = ChangeDisplaySettingsA(&newDisplayMode, 0);
      if (bDisplayChangeSuccessful != 0)
      {
         MessageBoxA((HWND)0x0, "Display change failed", "Error", 0);
      }
   }

   LPCSTR lpszWindowName = "Madagascar"; // TODO: LOAD FROM LANG FILES
   int y = 0;
   int x = 0;
   int uIconResourceId = 0x67;
   WNDPROC lpfnWndProc = MainWndProc;

   CreateMainWindow("RWSConsoleD3D8", lpszWindowName, x, y, g_nWindowWidth, g_nWindowHeight, lpfnWndProc, hInstance,
                    uIconResourceId, !g_bWindowedMode);

   RECT windowClientRect;
   RECT cursorClientRect;

   POINT windowCenter;

   RwVideoMode videoMode;

   if (theMainWindow != (HANDLE)0x0)
   {
      GetClientRect(theMainWindow, &windowClientRect);
      if (g_bWindowedMode == '\0')
      {
         videoMode.width = g_nWindowWidth;
         videoMode.height = g_nWindowHeight;
      }
      else
      {
         videoMode.width = windowClientRect.right - windowClientRect.left;
         videoMode.height = windowClientRect.bottom - windowClientRect.top;
      }
      videoMode.depth = 0x20;
      videoMode.flags = rwVIDEOMODEEXCLUSIVE;
      RwBool res = RWS::StartUp::Open(NULL, NULL, 0x1000000,
                                      videoMode, 0x10, theMainWindow);
      if (res != 0)
      {
         RWS::StartUp::LoadGameDatabaseFile("BOOTUP.DFF");
         // g_nWorldObjectCount = GetLoadedObjectCount();
         GetClientRect(theMainWindow, &cursorClientRect);
         windowCenter.x = (cursorClientRect.right - cursorClientRect.left) / 2;
         windowCenter.y = (cursorClientRect.bottom - cursorClientRect.top) / 2;
         ClientToScreen(theMainWindow, &windowCenter);
         SetCursorPos(windowCenter.x, windowCenter.y);
         // g_bGameRunning = 1;
         if (g_bWindowedMode != '\0')
         {
            ShowWindow(theMainWindow, 1);
         }
         ShowCursor(0);
         UpdateWindow(theMainWindow);
         while (!quit)
         {
            PumpMessages();
            while (true) // (g_bAppActive == '\0' && (quit == false))
            {
               PumpMessages();
               Sleep(10);
            }
            // RunGameFrame();
         }
         // FreeLevelResources();
         RWS::StartUp::Close();
      }
   }

   /*
   int result = 0;

   // Check to see if App is already running
   if (FindWindow(kMainWindowClassName, kMainWindowName))
   {
      // We have found the window so the framework is already running
      // Quit this version.

      RWS_RETURN(-1);
   }

   if (RegisterMainWindowClass(instance))
   {
#ifndef RWS_DESIGN
      // If were not in design mode, boot in a suitable res full screen.
      //
      int PosX    = 0;
      int PosY    = 0;
      int SizeX   = 640;
      int SizeY   = 480;

      const RwVideoModeFlag kFlags = static_cast<RwVideoModeFlag>(rwVIDEOMODEEXCLUSIVE);
#else
      // If we are in design mode, allow the user to set the window size etc
      //

      // Get initial size and position from registry
      int PosX    = StringToInt(RegGetString(kRegGroup, kRegName, "PosX", "300"));
      int PosY    = StringToInt(RegGetString(kRegGroup, kRegName, "PosY", "10"));
      int SizeX   = StringToInt(RegGetString(kRegGroup, kRegName, "SizeX", "640"));
      int SizeY   = StringToInt(RegGetString(kRegGroup, kRegName, "SizeY", "480"));

      const RwVideoModeFlag kFlags = static_cast<RwVideoModeFlag>(0);
#endif

      theMainWindow = CreateMainWindow(instance, PosX, PosY, SizeX, SizeY, kFlags);

      if (theMainWindow)
      {
         RECT clientRect;
         GetClientRect(theMainWindow, &clientRect);
         int clientWidth = clientRect.right - clientRect.left;
         int clientHeight = clientRect.bottom - clientRect.top;

         RwVideoMode videoModeInfo;

         videoModeInfo.width = clientWidth;
         videoModeInfo.height = clientHeight;
         videoModeInfo.depth = kBitDepth;
         videoModeInfo.flags = kFlags;

         if (RWS::StartUp::Open(
            0, // Use Defaults
            0, // Use Defaults
            (16 << 20), // Arena Size 16 Meg
            videoModeInfo,
            kZBitDepth,
            theMainWindow))
         {

#ifndef RWS_DESIGN

#define RWS_BOOTUP_FILE ".\\bootup.dff"

#pragma message ("RWS_DESIGN not defined booting from file, RWS_BOOTUP_FILE")

            StartUp::LoadGameDatabaseFile(RWS_BOOTUP_FILE);
#endif

            // Get maximized/minimized state from registry
            string maximized = RegGetString(kRegGroup, kRegName, "Maximized", "false");
            string minimized = RegGetString(kRegGroup, kRegName, "Minimized", "false");

            if (maximized == "true")
            {
               ShowWindow(theMainWindow, SW_MAXIMIZE);
            }
            else if (minimized == "true")
            {
               ShowWindow(theMainWindow, SW_MINIMIZE);
            }
            else
            {
               ShowWindow(theMainWindow, cmdShow);
            }

            UpdateWindow(theMainWindow);

            result = PumpMessages();

            RWS::StartUp::Close();
         }
      }
   }*/

   RWS_ASSERT(!IsWindow(theMainWindow), "theMainWindow hasn't been destroyed");

   if (hMutex != INVALID_HANDLE_VALUE)
   {
      CloseHandle(hMutex);
   }
   RWS_RETURN(1);
}
