#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>
#include <stdio.h>
#include <windows.h>

uint32_t MONS_Win32_ActToMode(char act)
{
  switch (act)
  {
    case MONS_SHOW_WINDOW:return SW_SHOWNORMAL;
    default:return -1;
  }
}

HANDLE MONS_Win32_CreateWindow(char* Title,MONS_Rect* rect,void* WinProc)
{
  if (!WinProc)
  {
    LOG("WinProc was NULL",MONSOON_LOG_ERROR,1);
    return NULL;
  }

  char* window_class_name = GetMemory(256);
  if (!window_class_name)
  {
    Error_Memory();
    return NULL;
  }

  snprintf(window_class_name, 256, "Monsoon Win32 Window: %d",__Monsoon -> state.WindowCount);;

  WNDCLASS window_class = {0};
  window_class.lpszClassName = window_class_name;
  window_class.lpfnWndProc = WinProc;

  if (!RegisterClassA(&window_class))
  {
    LOG("Unable to Register Class,Win32 ErrorCode = %d",MONSOON_LOG_ERROR,2,GetLastError());
    RemoveMemory(window_class_name);
    return NULL;
  }

  HANDLE WindowHandle = CreateWindowExA(
    0,
    window_class_name,
    Title,
    WS_OVERLAPPEDWINDOW,
    rect -> X,
    rect -> Y,
    rect -> Width,
    rect -> Height,
    NULL,
    NULL,
    NULL,
    NULL
  );

  if (!WindowHandle)
  {
    RemoveMemory(window_class_name);
    return NULL;
  }
  return WindowHandle;
}

MSBool MONS_Win32_CloseWindow(HANDLE Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,1);
    return False;
  }

  return DestroyWindow(Window);
}

MSBool MONS_Win32_WindowPollEvent(HANDLE Window)
{
  MSG msg;
  if (PeekMessage(&msg,NULL,0,0,True))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
