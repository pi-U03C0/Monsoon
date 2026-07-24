#include <Monsoon/Monsoon.h>
#include <Monsoon/Platform/Platform.h>
#include <Monsoon/SystemHeaders.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE: return 0;

        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect)
{
  LOG("Createing Window",MONSOON_LOG_INFO,10);

  if (!WinProc) //check proc
  {
    LOG("WinProc was NULL",MONSOON_LOG_ERROR,1);
    MONS_SetErrorCode(Make_Code(1));

    return NULL;
  }

  #ifdef _WIN32 //Create Window for Win32
     void* WindowHandle = MONS_Win32_CreateWindow(Title, rect, WinProc);
     uint64_t Code = MONS_Win32_GetErrorCode();
  #endif

  if (!WindowHandle) //check Window Handle
  {
    LOG("OS Window Handle was NULL,Window was not Create [%d]",MONSOON_LOG_ERROR,3,Code);
    MONS_SetErrorCode(Make_Code(3));
    return NULL;
  }

  LOG("Create Window %s at (%d,%d,%d,%d)",MONSOON_LOG_SUCCESS,11,Title,rect -> X,rect -> Y,rect -> Width ,rect -> Height);

  MONS_Window* window = GetMemory(sizeof(MONS_Window));
  if (!window) //check memory
  {
    Error_Memory();
    goto close_window;
  }

  //set Window value
  window -> OSHandle = WindowHandle;
  window -> WindowArea = rect;
  window -> Title = Title;

  __Monsoon -> state.WindowCount++;

  return window;

close_window:
  #ifdef _WIN32
     MONS_Win32_CloseWindow(WindowHandle);
  #endif
  return NULL;
}

MSBool MONS_CloseWindow(MONS_Window* Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,1);
    return False;
  }

  #ifdef _WIN32
     MSBool Success = MONS_Win32_CloseWindow(Window -> OSHandle);
     uint64_t Code = MONS_Win32_GetErrorCode();
  #endif

  LOG("Success=%d,Code=%d",MONSOON_LOG_DEBUG,255,Success,Code);

  if (Success)
  {
    LOG("Closed Window \"%s\"",MONSOON_LOG_INFO,3,Window -> Title);
    RemoveMemory(Window);
    __Monsoon -> state.WindowCount--;
  }
  else
  {
     LOG("Unable to Close Window \"%s\" Win32 Error %d",MONSOON_LOG_ERROR,2,Window -> Title,Code);
  }
  return Success;
}

MSBool MONS_ShoWindow(MONS_Window* Window,char act)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,1);
    return False;
  }

  int Mode = MONS_ActToMode(act);
  if (!Mode)
  {
    LOG("Invaild act %d",MONSOON_LOG_ERROR,4,act);
    return False;
  }

  #ifdef _WIN32
    MSBool Success = ShowWindow(Window -> OSHandle, Mode);
  #endif

  LOG("Success=%d,Mode=%d",MONSOON_LOG_DEBUG,255,Success,Mode);

  if (Success)
    LOG("Cannot Show Window \"%s\"",MONSOON_LOG_ERROR,2,Window -> Title);
  else
    LOG("Show Window \"%s\"",MONSOON_LOG_SUCCESS,3,Window -> Title);

  return Success;
}

int MONS_ActToMode(char act)
{
  #ifdef _WIN32
    switch (act)
    {
      case MONS_SHOW_WINDOW:return SW_SHOWNORMAL;
      default:return 0;
    }
  #endif
}

MONS_Event* MONS_WindowPollEvent(MONS_Window* Window)
{
  #ifdef _WIN32
     MONS_Win32_WindowPollEvent(Window -> OSHandle);
  #endif
}
