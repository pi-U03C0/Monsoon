#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/API/OpenGL/OpenGL.h>
#include <Monsoon/SystemHeaders.h>
#include <stdio.h>

MONS_DynamicLibrary* OpenGL32 = NULL;

MSBool MONS_InitComponentOpenGL()
{
  LOG("Initializ OpenGL",MONSOON_LOG_INFO,MONSOON_LOG_INIT);
  char* DLLPath = MONS_FindOpenGLDLL();

  OpenGL32 = MONS_LoadLibrary(DLLPath,0);

  MONS_LoadOpenGLCore();

  MONS_Window* Window = MONS_CreateWindow("Monsoon OpenGL Dummy Window",&(MONS_Rect){100,100,100,100});

  MONS_OpenGLContext* Context = MONS_CreateBasicOpenGLContext(Window);
  MONS_MakeCurrentOpenGLContext(Context);

  MONS_LoadOpenGLFunctions();
  LOG("Initialized OpenGL",MONSOON_LOG_INFO,MONSOON_LOG_INIT);

  return True;
}

char* MONS_FindOpenGLDLL()
{
  char* DLLPath = NULL;

  #ifdef MONSOON_PLATFORM_NT
     DLLPath = MONS_FindFile("OpenGL32.DLL",NULL,True);
  #endif

  #ifdef MONSOON_PLATFORM_POSIX
     DLLPath = MONS_FindFile("libGL.so.1","/lib:/usr/lib:/usr/lib/x86_64-linux-gnu",True);
  #endif

  return DLLPath;
}

void* MONS_LoadOpenGLFunction(char* ProcName)
{
  LOG("ProcName = %s",MONSOON_LOG_DEBUG,255,ProcName);
  void* address = glGetProcAddress(ProcName);
  if (!address)
  {
    address = MONS_GetProcAddress(ProcName, OpenGL32);
  }
  return address;
}

MSBool MONS_LoadOpenGLCore()
{
  glGetProcAddress = (PFNWGLGETPROCADDRESSPROC)MONS_GetProcAddress(sglGetProcAddress,OpenGL32);
  glCreateContext = (PFNWGLCREATECONTEXTPROC)MONS_GetProcAddress(sglCreateContext,OpenGL32);
  glMakeCurrent = (PFNWGLMAKECURRENTPROC)MONS_GetProcAddress(sglMakeCurrent,OpenGL32);
  glDeleteContext = (PFNWGLDELETECONTEXTPROC)MONS_GetProcAddress(sglDeleteContext,OpenGL32);

  return True;
}

MSBool MONS_CreateDummyOpenGLContext(MONS_Window* Window)
{
  return True;
}

MSBool MONS_LoadOpenGLFunctions()
{
  glGetString = (PFNGLGETSTRINGPROC)MONS_LoadOpenGLFunction(sglGetString);

  return True;
}

void MONS_TerminateComponentOpenGL()
{
  //MONS_UnLoadOpenGLFunctions();
}
