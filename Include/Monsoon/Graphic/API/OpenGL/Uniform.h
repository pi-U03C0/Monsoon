#ifndef MONSOON_GRAPGIC_API_OPENGL_UNIFORM_H
#define MONSOON_GRAPGIC_API_OPENGL_UNIFORM_H

#include <Monsoon/Monsoon.h>

MONS_API MSBool MONS_QureyOpenGLShaderUniforms(MONS_OpenGLShader* Shader);

MONS_API MONS_OpenGLShaderUniform* MONS_FindOpenGLUniformFromName(MONS_OpenGLShader* Shader,char* Name);

#endif
