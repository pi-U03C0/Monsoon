#include <Monsoon/Monsoon.h>
#include <stdio.h>

MSBool MONS_InitComponentOpenGL()
{
  LOG("Initializ OpenGL",MONSOON_LOG_INFO,MONSOON_LOG_INIT);
  char* DLLPath = MONS_FindOpenGLDLL();

  return True;
}

char* MONS_FindOpenGLDLL()
{
  char* DLLPath = NULL;

  #ifdef MONSOON_PLATFORM_NT
     DLLPath = MONS_FindFile("OpenGL32.DLL",NULL,True);
  #endif

  #ifdef MONSOON_PLATFORM_POSIX
     DLLPath = MONS_FindFile("libGL.so.1")
  #endif

  MONS_DynamicLibrary* OpenGL_Library = MONS_LoadLibrary(DLLPath,0);

  return NULL;
}

MSBool MONS_LoadOpenGLFunctions(char* DLLPath)
{
  MONS_LoadLibrary(DLLPath,0);
  return True;
}
