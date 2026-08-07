#include <Monsoon/Monsoon.h>

MSBool MONS_InitComponentOpenGL()
{
  LOG("Initializ OpenGL",MONSOON_LOG_INFO,MONSOON_LOG_INIT);
  char* DLLPath = MONS_FindOpenGLDLL();

  return True;
}

char* MONS_FindOpenGLDLL()
{
  #ifdef MONSOON_PLATFORM_NT
     MONS_FindFile("OpenGL32.DLL");
  #endif

  return NULL;
}

MSBool MONS_LoadOpenGLFunctions(char* DLLPath)
{
  MONS_LoadLibrary(DLLPath,0);
  return True;
}
