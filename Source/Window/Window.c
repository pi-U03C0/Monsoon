#include "Monsoon/MONS_Log.h"
#include <Monsoon/Monsoon.h>
#include <stdio.h>

MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect,void* WinProc)
{
  printf("dskdjkkkkkkkkk\n");
  if (!WinProc)
  {
    LOG("WinProc was NULL",MONSOON_LOG_ERROR,1);
    return NULL;
  }

  char* window_name = GetMemory(256);
  MONS_Window* window = GetMemory(sizeof(MONS_Window*));

  snprintf(window_name, 256, "Monsoon Win32 Window: %d",__Monsoon -> state.WindowCount);

  WNDCLASSA window_class = {0};
  window_class.lpfnWndProc = WinProc;
  window_class.hInstance = NULL;
  window_class.lpszClassName = window_name;

  if (!RegisterClassA(&window_class))
  {
    __Monsoon -> Error.Code = 0x009;

    return NULL;
  }

  HANDLE WindowHendle = CreateWindowExA(
      0,
      window_class.lpszClassName,
      Title,
      0,
      rect -> X,
      rect -> Y,
      rect -> Width,
      rect -> Height,
      NULL,
      NULL,
      NULL,
      NULL
  );

  window -> OSHandle = WindowHendle;
  window -> WindowArea = rect;

  return window;
}
