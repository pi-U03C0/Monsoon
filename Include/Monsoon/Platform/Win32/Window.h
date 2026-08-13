#ifndef MONSOON_WIN32_WINDOW_H
#define MONSOON_WIN32_WINDOW_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/SystemHeaders.h>
#include <Monsoon/Monsoon.h>

#define MONSOON_PROC_WIN32_WINDOW_NAME "MONS_Win32_WindowProc"

//Monsoon Win32 WindowProc
MONS_API LRESULT CALLBACK MONS_Win32_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);;

//Win32 Create Window runing directly Win32 API functions
MONS_API HANDLE MONS_Win32_CreateWindow(char* window_name,MONS_Rect* rect,void* WinProc);

//Win32 Close Window runing CloseWindow directly
MONS_API MSBool MONS_Win32_CloseWindow(HANDLE Window);

//Running the Win32 Window Message Loop return Monsoon Event Pointer
MONS_API MSBool MONS_Win32_WindowPollEvent(HANDLE Window);

MONS_API uint32_t MONS_Win32_ActToMode(char act);

MONS_API void* MONS_Win32_GetWindowDrawSurface(HANDLE Window);

MONS_API MSBool MONS_Win32_SetPixelFormat(HDC WindowDC);

#endif
