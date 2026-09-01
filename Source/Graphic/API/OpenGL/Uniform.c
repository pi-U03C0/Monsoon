#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <stdio.h>

MSBool MONS_QureyOpenGLShaderUniforms(MONS_OpenGLShader* Shader)
{
  if (!Shader)
  {
    LOG("Shader was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  int32_t MaxUniformNameLength = 0;

  glGetProgramiv(Shader -> ShaderProgrameHandle,GL_ACTIVE_UNIFORM_MAX_LENGTH,&MaxUniformNameLength);
  if (MaxUniformNameLength >= MONSOON_OPENGL_MAX_UNIFORM_LENGTH)
  {
    MONS_SetErrorCode(Make_Code(MONSOON_LOG_TOO_LONG));
    return False;
  }

  glGetProgramiv(Shader -> ShaderProgrameHandle,GL_ACTIVE_UNIFORMS,(int*)&Shader -> UniformCount);

  Shader -> ShaderUniforms = GetMemory(sizeof(MONS_OpenGLShaderUniform)*Shader -> UniformCount);
  if (!Shader -> ShaderUniforms)
  {
    Error_Memory();
    return False;
  }

  for (uint16_t i = 0 ; i < Shader -> UniformCount ; i++)
  {
    GLsizei Length;
    GLint Size;
    GLenum Type;

    glGetActiveUniform(
        Shader -> ShaderProgrameHandle,
        i,
        MaxUniformNameLength,
        &Length,
        &Size,
        &Type,
        Shader -> ShaderUniforms[i].UniformName
    );

    Shader -> ShaderUniforms[i].GLType = Type;
    Shader -> ShaderUniforms[i].Size = Size;
    Shader -> ShaderUniforms[i].ID = glGetUniformLocation(Shader -> ShaderProgrameHandle,Shader -> ShaderUniforms[i].UniformName);
  }

  return True;
}

MSBool MONS_SetOpenGLShaderUniformInt(MONS_OpenGLShader* Shader,uint64_t Data,uint64_t GLType)
{
  return True;
}

