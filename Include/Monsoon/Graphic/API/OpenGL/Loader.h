#ifndef MONSOON_GRAPHIC_API_OPENGL_LOADER
#define MONSOON_GRAPHIC_API_OPENGL_LOADER

#include <Monsoon/MONS_Types.h>

char* MONS_FindOpenGLDLL();

MSBool MONS_InitComponentOpenGL();

MSBool MONS_LoadOpenGLCore();

MSBool MONS_LoadOpenGLFunctions();

#endif
