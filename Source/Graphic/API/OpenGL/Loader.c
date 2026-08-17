#include "Monsoon/Graphic/API/OpenGL/GL/glcorearb.h"
#include "Monsoon/Graphic/API/OpenGL/fnOpenGL.h"
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
  MONS_RemoveCurrentOpenGLContect();
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
  void* address = glGetProcAddress(ProcName);
  if (!address)
  {
    address = MONS_GetProcAddress(ProcName, OpenGL32);
  }
  LOG("ProcName = %s,address = 0x%p",MONSOON_LOG_DEBUG,255,ProcName,address);
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
  glCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)MONS_LoadOpenGLFunction(sglCreateContextAttribsARB);
  glClearColor = (PFNGLCLEARCOLORPROC)MONS_LoadOpenGLFunction(sglClearColor);
  glClear = (PFNGLCLEARPROC)MONS_LoadOpenGLFunction(sglClear);
  glClearColor = (PFNGLCLEARCOLORPROC)MONS_LoadOpenGLFunction(sglClearColor);
  glCreateShader = (PFNGLCREATESHADERPROC)MONS_LoadOpenGLFunction(sglCreateShader);
  glShaderSource = (PFNGLSHADERSOURCEPROC)MONS_LoadOpenGLFunction(sglShaderSource);
  glGetShaderiv = (PFNGLGETSHADERIVPROC)MONS_LoadOpenGLFunction(sglGetShaderiv);
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)MONS_LoadOpenGLFunction(sglGetShaderInfoLog);
  glCreateProgram = (PFNGLCREATEPROGRAMPROC)MONS_LoadOpenGLFunction(sglCreateProgram);
  glAttachShader = (PFNGLATTACHSHADERPROC)MONS_LoadOpenGLFunction(sglAttachShader);
  glLinkProgram = (PFNGLLINKPROGRAMPROC)MONS_LoadOpenGLFunction(sglLinkProgram);
  glGetProgramiv =  (PFNGLGETPROGRAMIVPROC)MONS_LoadOpenGLFunction(sglGetProgramiv);
  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)MONS_LoadOpenGLFunction(sglGetProgramInfoLog);
  glGenBuffers = (PFNGLGENBUFFERSPROC)MONS_LoadOpenGLFunction(sglGenBuffers);
  glBindBuffer = (PFNGLBINDBUFFERPROC)MONS_LoadOpenGLFunction(sglBindBuffer);
  glBufferData = (PFNGLBUFFERDATAPROC)MONS_LoadOpenGLFunction(sglBufferData);
  glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)MONS_LoadOpenGLFunction(sglEnableVertexAttribArray);
  glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)MONS_LoadOpenGLFunction(sglVertexAttribPointer);
  glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)MONS_LoadOpenGLFunction(sglBindVertexArray);
  glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)MONS_LoadOpenGLFunction(sglGenVertexArrays);
  glDrawElements = (PFNGLDRAWELEMENTSPROC)MONS_LoadOpenGLFunction(sglDrawElements);
  glUseProgram = (PFNGLUSEPROGRAMPROC)MONS_LoadOpenGLFunction(sglUseProgram);
  glCompileShader = (PFNGLCOMPILESHADERPROC)MONS_LoadOpenGLFunction(sglCompileShader);

  return True;
}

void MONS_TerminateComponentOpenGL()
{
  //MONS_UnLoadOpenGLFunctions();
}
