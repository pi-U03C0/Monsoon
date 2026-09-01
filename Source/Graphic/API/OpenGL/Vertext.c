#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

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

MSBool MONS_CreateOpenGLElementBufferObject(MONS_OpenGLVertextData* Vertext,uint32_t* Indices,uint32_t IndicesCount)
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
