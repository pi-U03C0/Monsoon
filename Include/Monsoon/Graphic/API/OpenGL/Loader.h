#ifndef MONSOON_GRAPHIC_API_OPENGL_LOADER
#define MONSOON_GRAPHIC_API_OPENGL_LOADER

#include <Monsoon/Monsoon.h>

//The Index that OpenGL Component is at in MONS_Components
MONS_API extern uint8_t MONS_OpenGLComponent;
MONS_API extern MONS_OpenGLStorage* MONS_OpenGLCompoentStorage;

MONS_API char* MONS_FindOpenGLDLL();
MONS_API MSBool MONS_InitComponentOpenGL(MONS_ComponentList* ComponentList)
MONS_API MSBool MONS_LoadOpenGLCore();
MONS_API MSBool MONS_LoadOpenGLFunctions();
MONS_API MSBool MONS_DeInitComponentOpenGL();
MONS_API MSBool MONS_UnLoadOpenGLFunctions();

#endif
