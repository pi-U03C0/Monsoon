#include "Monsoon/Graphic/API/OpenGL/GL/glcorearb.h"
#include "Monsoon/Graphic/API/OpenGL/fnOpenGL.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <stdio.h>

MSBool MONS_CompileOpenGLShader(MONS_OpenGLShader* Shader,char* VertextSource,char* FragmentSource)
{
  if (!Shader)
  {
     LOG("Shader was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
     return False;
  }

  Shader -> VertexSource = MONS_DupeString(VertextSource);
  Shader -> FragmentSource = MONS_DupeString(FragmentSource);
  Shader -> FragmentShaderHandle = 0;
  Shader -> VertexShaderHandle = 0;
  Shader -> ShaderProgrameHandle = 0;
  Shader -> ShaderUniforms = NULL;

  int Success = 0;
  char Log[512];

  //Compile Vertext shader
  Shader -> VertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(Shader -> VertexShaderHandle, 1, (const char**)&Shader -> VertexSource, NULL);
  glCompileShader(Shader -> VertexShaderHandle);

  //checkk Success if not log and return
  glGetShaderiv(Shader -> VertexShaderHandle, GL_COMPILE_STATUS, &Success);
  if (!Success)
  {
    glGetShaderInfoLog(Shader -> VertexShaderHandle, 512, NULL, Log);
    LOG("Unable to Compile Vertex Shader\n%s",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
    return False;
  }

  //Compile Fragment Shader
  Shader -> FragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(Shader -> FragmentShaderHandle, 1, (const char**)&Shader -> FragmentSource, NULL);
  glCompileShader(Shader -> FragmentShaderHandle);

  //checkk Success if not log and return
  glGetShaderiv(Shader -> FragmentShaderHandle, GL_COMPILE_STATUS, &Success);
  LOG("Success = %d",MONSOON_LOG_DEBUG,255,Success);
  if (!Success)
  {
    glGetShaderInfoLog(Shader -> FragmentShaderHandle, 512, NULL, Log);
    LOG("Unable to Compile FRAGMENT Shader\n%s",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO,Log);
    return False;
  }

  LOG("Compile Shader",MONSOON_LOG_SUCCESS,0);

  return True;
}

MSBool MONS_CreateAndLinkOpenGLShaderProgram(MONS_OpenGLShader* Shader)
{
  if (!Shader)
  {
     LOG("Shader was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
     return False;
  }

  if (!(Shader -> FragmentSource) || !(Shader -> VertexSource))
  {
    LOG("Shader Source was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  if (!(Shader -> VertexShaderHandle) || !(Shader -> FragmentShaderHandle))
  {
    LOG("Shader Handle was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
    return False;
  }

  int Success = 0;
  char Log[1024];

  //Create a Shader Programe and link it
  Shader -> ShaderProgrameHandle =  glCreateProgram();
  glAttachShader(Shader -> ShaderProgrameHandle,Shader -> VertexShaderHandle);
  glAttachShader(Shader -> ShaderProgrameHandle,Shader -> FragmentShaderHandle);
  glLinkProgram(Shader -> ShaderProgrameHandle);

  //checkk Success if not log and return
  glGetProgramiv(Shader -> ShaderProgrameHandle, GL_LINK_STATUS, &Success);
  if (!Success)
  {
    glGetProgramInfoLog(Shader -> ShaderProgrameHandle, 512, NULL,Log);
    LOG("Unable to Link Shader Programe\n%s",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
    return False;
  }
  LOG("Link Shader Programe",MONSOON_LOG_SUCCESS,0);

  return True;
}

MSBool MONS_FreeOpenGLShader(MONS_OpenGLShader* Shader)
{
  if (!Shader)
  {
    LOG("Shader was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if(!Shader -> FragmentSource)
     RemoveMemory(Shader -> FragmentSource);

  if (!Shader -> VertexSource)
    RemoveMemory(Shader -> VertexSource);

  if (!Shader -> VertexShaderHandle)
    glDeleteShader(Shader -> VertexShaderHandle);

  if (!Shader -> FragmentShaderHandle)
    glDeleteShader(Shader -> FragmentShaderHandle);

  if (!Shader -> ShaderProgrameHandle)
    glDeleteProgram(Shader -> ShaderProgrameHandle);

  return True;
}

uint32_t MONS_GetCurrentOpenGLPrograme()
{
  int32_t Progame;
  glGetIntegerv(GL_CURRENT_PROGRAM,&Progame);
  return Progame;
}
