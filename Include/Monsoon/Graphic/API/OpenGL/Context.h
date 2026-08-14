#ifndef MONSOON_GRAPHIC_API_OPENGL_GL_CONTEXT_H
#define MONSOON_GRAPHIC_API_OPENGL_GL_CONTEXT_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Monsoon.h>

MONS_API MONS_OpenGLContext* MONS_CreateBasicOpenGLContext(MONS_Window* Window);
MONS_API MSBool MONS_MakeCurrentOpenGLContext(MONS_OpenGLContext* Context);
MONS_API MSBool MONS_RemoveCurrentOpenGLContect();
MONS_API MONS_OpenGLContext* MONS_CreateOpenGLContext(MONS_Window* Window,int* GLAttributes);

#endif

