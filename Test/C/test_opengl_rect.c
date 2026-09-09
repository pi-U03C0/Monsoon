#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <cglm/cglm.h>
#include <stdio.h>

MONS_OpenGLShader Shader = {0};
MONS_OpenGLVertextData Vertext = {0};

float vertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3 
};

MONS_Window* Window = NULL;
MONS_OpenGLContext* Context = NULL;
mat4 WindowMat = {0};
float CoordintionX = 250.0f;
float CoordintionY = 250.0f;

MSBool CompileShader()
{
  char* ShaderSource = GetMemory(1024);
  MONS_File* ShaderFile = MONS_OpenFile("Library/Shaders/Coordinations.2D.glsl",MONSOON_FILE_READ_WRITE);

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
  glUniformMatrix4fv(MONS_FindOpenGLUniformFromName(&Shader, "ScreenMat") -> ID,1,False,(float*)WindowMat);
  glUniform2f(MONS_FindOpenGLUniformFromName(&Shader, "Coordinations") -> ID,CoordintionX,CoordintionY);
  glUniform2f(MONS_FindOpenGLUniformFromName(&Shader, "WidthAndHeight") -> ID,50.0f,50.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(MONSOON_COMPONENT_OPENGL), MONSOON_LOG_INFO))
  {
    printf("Unable to Init Monsoon\n");
    return 1;
  }

  Window = MONS_CreateWindow("Monsoon Test: test_opengl_rect Move with HJKL",&(MONS_Rect){100,100,600,600});
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);
  glm_ortho(0,Window -> WindowArea -> Width,Window -> WindowArea -> Height,0,-1.0f,1.0,WindowMat);

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
      if (Event -> Type == MONSOON_EVENT_WINDOW_CHANGE_SIZE)
      {
        glm_ortho(0,Window -> WindowArea -> Width,Window -> WindowArea -> Height,0,-1.0f,1.0,WindowMat);
      }
      if (Event -> Type == MONSOON_EVENT_KEY_DOWN)
      {
        if (((MONS_WindowPrarmKey*)Event -> Prarms) -> Key == '')
        {
          IsRunning = False;
        }
        if (((MONS_WindowPrarmKey*)Event -> Prarms) -> Key == 'H')
        {
           CoordintionX -= 1.0f;
        }
        if (((MONS_WindowPrarmKey*)Event -> Prarms) -> Key == 'L')
        {
           CoordintionX += 1.0f;
        }
        if (((MONS_WindowPrarmKey*)Event -> Prarms) -> Key == 'K')
        {
           CoordintionY -= 1.0f;
        }
        if (((MONS_WindowPrarmKey*)Event -> Prarms) -> Key == 'J')
        {
           CoordintionY += 1.0f;
        }
      }
    }

    Render();
    MONS_SwapWindowDrawBuffers(Window);
  }

  MONS_FreeOpenGLShader(&Shader);
  MONS_CloseWindow(Window);

  MONSTerminate();
  return 0;
}
