#ifndef MONSOON_GRAPGIC_API_OPENGL_SHADER_H
#define MONSOON_GRAPGIC_API_OPENGL_SHADER_H
#include <Monsoon/Monsoon.h>

MONS_API MSBool MONS_CompileOpenGLShader(MONS_OpenGLShader* Shader,char* VertextSource,char* FragmentSource);

MONS_API MSBool MONS_CreateAndLinkOpenGLShaderProgram(MONS_OpenGLShader* Shader);

MONS_API MSBool MONS_CreateOpenGLVertextBufferObject(MONS_OpenGLVertextData* Vertext,float* Vertices,uint32_t Count);

MONS_API MSBool MONS_CreateOpenGLVertextArrayObject(MONS_OpenGLVertextData* Vertext);

MONS_API MSBool MONS_CreateOpenGLVertextElementObject(MONS_OpenGLVertextData* Vertext,uint32_t* Indices,uint32_t IndicesCount);

#endif
