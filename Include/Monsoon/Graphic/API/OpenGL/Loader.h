#ifndef MONSOON_GRAPHIC_API_OPENGL_LOADER
#define MONSOON_GRAPHIC_API_OPENGL_LOADER

#include <Monsoon/Monsoon.h>

//The Index that OpenGL Component is at in MONS_Components
MONS_API extern uint16_t MONS_OpenGLComponent;

char* MONS_FindOpenGLDLL();

MSBool MONS_InitComponentOpenGL();

MSBool MONS_LoadOpenGLCore();

MSBool MONS_LoadOpenGLFunctions();

MSBool MONS_DeInitComponentOpenGL();

#endif
