#include <Monsoon/Monsoon.h>

MSBool MONS_InitComponentOpenGL()
{
  MONS_WriteStdOutput("Init OpenGL32");
  return True;
}

char* MONS_FindOpenGLDLL()
{
  #ifdef MONSOON_PLATFORM_NT
     MONS_FindFile("OpenGL32.DLL");
  #endif
  return NULL;
}

MSBool MONS_LoadOpenGLFunctions()
{
  MONS_LoadLibrary("OpenGL32.DLL",0);
  return True;
}
