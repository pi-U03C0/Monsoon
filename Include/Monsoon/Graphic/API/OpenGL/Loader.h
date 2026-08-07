#ifndef MONSOON_GRAPHIC_API_OPENGL_LOADER
#define MONSOON_GRAPHIC_API_OPENGL_LOADER

#include <Monsoon/MONS_Types.h>

MSBool MONS_LoadOpenGLFunctions(char* DLLPath);
;
char* MONS_FindOpenGLDLL();

MSBool MONS_InitComponentOpenGL();

#endif
