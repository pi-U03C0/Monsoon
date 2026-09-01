#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <cglm/cglm.h>
#include <stdio.h>

MONS_OpenGLShader Shader = {0};
MONS_OpenGLVertextData Vertext = {0};

float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

MONS_Window* Window = NULL;
MONS_OpenGLContext* Context = NULL;

MSBool CompileShader()
{
  char* ShaderSource = GetMemory(1024);
  MONS_File* ShaderFile = MONS_OpenFile("Library/Shaders/Coordinations.glsl",MONSOON_FILE_READ_WRITE);
  if (!ShaderFile)
  {
    return False;
  }

  MONS_ReadFile(ShaderFile, ShaderSource,ShaderFile -> FileSize);
  char** SplitSource = MONS_SplitString(ShaderSource,'');

  MONS_CompileOpenGLShader(&Shader,SplitSource[0],SplitSource[1]);
  MONS_CreateAndLinkOpenGLShaderProgram(&Shader);
  MONS_CreateOpenGLVertextBufferObject(&Vertext,vertices,12);
  MONS_CreateOpenGLVertextArrayObject(&Vertext);
  MONS_CreateOpenGLElementBufferObject(&Vertext,indices,6);
  MONS_QureyOpenGLShaderUniforms(&Shader);

  glUseProgram(Shader.ShaderProgrameHandle);
  return True;
}

void Render()
{
  glUniform3f(Shader.ShaderUniforms[0].ID,0.1f,0.1f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(MONSOON_COMPONENT_OPENGL), MONSOON_LOG_SUCCESS))
  {
    printf("Unable to Init Monsoon\n");
    return 1;
  }

  Window = MONS_CreateWindow("Monsoon Test: test_opengl_rect",&(MONS_Rect){100,100,600,600});
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);

  Context = MONS_CreateOpenGLContext(Window,NULL);
  MONS_MakeCurrentOpenGLContext(Context);

  CompileShader();

  glClearColor(0.5f,0.9f,0.2f,0.1f);

  MONS_Event* Event = NULL;
  while (IsRunning)
  {
    MONS_PollWindowEvent(Window);
    Event = MONS_PopWindowEvent(Window);
    if (Event)
    {
      if (Event -> Type == MONSOON_EVENT_WINDOW_CLOSE)
      {
        IsRunning = False;
      }
    }

    Render();
    MONS_SwapWindowDrawBuffers(Window);
  }

  MONS_FreeOpenGLShader(&Shader);

  MONSTerminate();
  return 0;
}
