#include "Monsoon/Graphic/API/OpenGL/fnOpenGL.h"
#include <Monsoon/Monsoon.h>

MSBool MONS_CompileOpenGLShader(MONS_OpenGLShader* Shader,char* VertextSource,char* FragmentSource)
{
  if (!Shader)
  {
     LOG("Shader was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
     return False;
  }

  Shader -> VertexSource = VertextSource;
  Shader -> FragmentSource = FragmentSource;

  int Success = 0;
  char Log[1024];

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
  if (!Success)
  {
    glGetShaderInfoLog(Shader -> FragmentShaderHandle, 512, NULL, Log);
    LOG("Unable to Compile FRAGMENT Shader\n%s",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
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

MSBool MONS_CreateOpenGLVertextBufferObject(MONS_OpenGLVertextData* Vertext,float* Vertices,uint32_t Count)
{
  if (!Vertext)
  {
    LOG("Vertext was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  Vertext -> Vertices = Vertices;
  Vertext -> VerticesCount = Count;

  glGenBuffers(1,&(Vertext -> VertextBufferObject));
  glBindBuffer(GL_ARRAY_BUFFER,Vertext -> VertextBufferObject);
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*(Vertext -> VerticesCount),Vertext -> Vertices,GL_STATIC_DRAW);
  LOG("Create OpenGL VertextBufferObject at index %d",MONSOON_LOG_SUCCESS,0,Vertext -> VertextBufferObject);

  return True;
}

MSBool MONS_CreateOpenGLVertextArrayObject(MONS_OpenGLVertextData* Vertext)
{
  if (!Vertext)
  {
    LOG("Vertext was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  glGenVertexArrays(1,&Vertext -> VertextArrayObject);
  glBindVertexArray(Vertext -> VertextArrayObject);
  glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,3 * sizeof(float),NULL);
  glEnableVertexAttribArray(0);

  return True;
}

MSBool MONS_CreateOpenGLVertextElementObject(MONS_OpenGLVertextData* Vertext,uint32_t* Indices,uint32_t IndicesCount)
{
  if (!Vertext)
  {
    LOG("Vertext was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if (!Indices)
  {
    LOG("Indices was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  Vertext -> Indices = Indices;
  Vertext -> IndicesCount = IndicesCount;

  glGenBuffers(1,&Vertext -> ElementBufferObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Vertext -> ElementBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Vertext -> IndicesCount*sizeof(uint32_t), Indices, GL_STATIC_DRAW);

  return True;
}
