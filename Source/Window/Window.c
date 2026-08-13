#include <Monsoon/Monsoon.h>
#include <Monsoon/Platform/Platform.h>
#include <Monsoon/SystemHeaders.h>

MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect)
{
  LOG("Createing Window",MONSOON_LOG_INFO,10);

  void* proc = MONS_GetProc(MONS_PROC_WINDOW);
  if (!proc)
  {
    LOG("Window proc was NULL",MONSOON_LOG_ERROR,11);
    return NULL;
  }

  MONS_Window* Window = GetMemory(sizeof(MONS_Window));
  if (!Window) //check memory
  {
    Error_Memory();
    return NULL;
  }

  #ifdef _WIN32 //Create Window for Win32
     OSHandle WindowHandle = MONS_Win32_CreateWindow(Title, rect, proc);
     uint64_t Code = MONS_Win32_GetErrorCode();

    if (!WindowHandle) //check Window Handle
    {
      LOG("OS Window Handle was NULL,Window was not Create [%d]",MONSOON_LOG_ERROR,3,Code);
      MONS_SetErrorCode(Make_Code(3));
      return NULL;
    }

    SetWindowLongPtrA(WindowHandle,GWLP_USERDATA,(LONG_PTR)Window);
  #endif

  LOG("Create Window \"%s\" at (%d,%d,%d,%d)",MONSOON_LOG_SUCCESS,11,Title,rect -> X,rect -> Y,rect -> Width ,rect -> Height);

  //set Window value
  Window -> OSHandle = WindowHandle;
  Window -> WindowArea = rect;
  Window -> Title = Title;
  Window -> Events = MONS_InitQueue(256);
  Window -> RenderSurface = MONS_GetWindowDrawSurface(Window);

  if (!Window -> Events)
  {
    LOG("Unable to Create Window Event Queue",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    goto close_window;
  }

  __Monsoon -> state.WindowCount++;

  return Window;

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
    MONS_TerminateQueue(Window -> Events);
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

MSBool MONS_PollWindowEvent(MONS_Window* Window)
{
  #ifdef _WIN32
     return MONS_Win32_WindowPollEvent(Window -> OSHandle);
  #endif
}

MONS_Event* MONS_PopWindowEvent(MONS_Window* Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,1);
    return NULL;
  }
  return  (MONS_Event*)MONS_PopQueue(Window -> Events);
}

MSBool MONS_PushWindowEvent(MONS_Window* Window,MONS_Event* Event)
{
  return MONS_PushQueue(Window -> Events, (uint64_t)Event);
}
