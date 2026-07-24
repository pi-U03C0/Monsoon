#ifndef MONSOON_WIN32_WINDOW_H
#define MONSOON_WIN32_WINDOW_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/SystemHeaders.h>

HANDLE MONS_Win32_CreateWindow(char* window_name,MONS_Rect* rect,void* WinProc);
MSBool MONS_Win32_CloseWindow(HANDLE Window);
MSBool MONS_Win32_WindowPollEvent(HANDLE Window);

uint32_t MONS_Win32_ActToMode(char act);

#endif
