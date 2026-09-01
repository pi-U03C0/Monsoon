#ifndef MONSOON_GRAPHIC_API_OPENGL_VERTEXT_H
#define MONSOON_GRAPHIC_API_OPENGL_VERTEXT_H

#include <Monsoon/Monsoon.h>

MONS_API MSBool MONS_CreateOpenGLVertextBufferObject(MONS_OpenGLVertextData* Vertext,float* Vertices,uint32_t Count);

MONS_API MSBool MONS_CreateOpenGLVertextArrayObject(MONS_OpenGLVertextData* Vertext);

MONS_API MSBool MONS_CreateOpenGLElementBufferObject(MONS_OpenGLVertextData* Vertext,uint32_t* Indices,uint32_t IndicesCount);

#endif
