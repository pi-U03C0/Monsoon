#ifndef MONSOON_GRAPHIC_API_OPENGL_GL_CONTEXT_H
#define MONSOON_GRAPHIC_API_OPENGL_GL_CONTEXT_H

#include <Monsoon/MONS_Types.h>

MONS_OpenGLContext* MONS_CreateBasicOpenGLContext(MONS_Window* Window);
MSBool MONS_MakeCurrentOpenGLContext(MONS_OpenGLContext* Context);
MSBool MONS_RemoveCurrentOpenGLContect();

#endif

