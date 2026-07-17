#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

#include <stdio.h>
#include <windows.h>

MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect,void* WinProc)
{
  #if MONSOON_LOG_LEVEL >= MONSOON_LOG_INFO
     LOG("Createing Window",MONSOON_LOG_INFO,10);
  #endif

  if (!WinProc)
  {
    #if MONSOON_LOG_LEVEL >= MONSOON_LOG_ERROR
      LOG("WinProc was NULL",MONSOON_LOG_ERROR,1);
    #endif

    return NULL;
  }

  char* window_name =   GetMemory(256);
  MONS_Window* window = GetMemory(sizeof(MONS_Window));

  if (!window || !window_name)
  {
    Error_Memory();
    return NULL;
  }

  snprintf(window_name, 256, "Monsoon Win32 Window: %d",__Monsoon -> state.WindowCount);

  #ifdef _WIN32

  WNDCLASSA window_class = {0};
  window_class.lpfnWndProc = WinProc;
  window_class.hInstance = NULL;
  window_class.lpszClassName = window_name;

  if (!RegisterClassA(&window_class))
  {
    RemoveMemory(window_name);
    RemoveMemory(window);

    #if MONSOON_LOG_LEVEL >= MONSOON_LOG_ERROR
       LOG("Unable to Register Window class name=%s",MONSOON_LOG_ERROR,2,window_class.lpszClassName);
    #endif

    return NULL;
  }

  HANDLE WindowHandle = CreateWindowExA(
      0,
      window_class.lpszClassName,
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
  #endif

  if (!WindowHandle)
  {
    #if MONSOON_LOG_LEVEL >= MONSOON_LOG_ERROR
      LOG("OS Window Handle was NULL,Window was not Create",MONSOON_LOG_ERROR,3);
    #endif

    MONS_SetErrorCode(Make_Code(3));
    return NULL;
  }

  #if MONSOON_LOG_LEVEL >= MONSOON_LOG_INFO
     LOG("Create Window %s at (%d,%d,%d,%d)",MONSOON_LOG_INFO,11,Title,rect -> X,rect -> Y,rect -> Width ,rect -> Height);
  #endif

  window -> OSHandle = WindowHandle;
  window -> WindowArea = rect;

  __Monsoon -> state.WindowCount++;

  return window;
}

MSBool MONS_CloseWindow(MONS_Window* Window)
{
  #ifdef _WIN32
    return CloseWindow(Window -> OSHandle);
    RemoveMemory(Window);
  #endif

}

MSBool MONS_ShoWindow(MONS_Window* Window,char act)
{
  int Mode = MONS_ActToMode(act);
  if (!Mode)
  {
      return False;
  }

  #ifdef _WIN32
    return ShowWindow(Window -> OSHandle, Mode);
  #endif
}

int MONS_ActToMode(char act)
{
  #ifdef _WIN32
    switch (act)
    {
      case MONS_SHOW_WINDOW:return SW_SHOWNORMAL;
      default:return -1;
    }
  #endif
}
