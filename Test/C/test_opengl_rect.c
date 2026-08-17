#include "Monsoon/Graphic/API/OpenGL/GL/glcorearb.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <stdio.h>

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

char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(MONSOON_INIT_OPENGL),MONSOON_LOG_INFO))
  {
     printf("Unable to Init Monsoon\n");
     return False;
  }

  MONS_Window* Window = MONS_CreateWindow(
    "Monsoon: OpenGL Render Test",
    &(MONS_Rect){200,200,400,400}
  );

  MONS_ShoWindow(Window, MONS_SHOW_WINDOW);

  MONS_OpenGLContext* Context = MONS_CreateOpenGLContext(Window, NULL);
  MONS_MakeCurrentOpenGLContext(Context);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  MONS_OpenGLShader Shader = {0};

  MONS_OpenGLVertextData Vertext = {0};

  MONS_CompileOpenGLShader(&Shader,vertexShaderSource,fragmentShaderSource);
  MONS_CreateAndLinkOpenGLShaderProgram(&Shader);
  MONS_CreateOpenGLVertextBufferObject(&Vertext,vertices,12);
  MONS_CreateOpenGLVertextArrayObject(&Vertext);
  MONS_CreateOpenGLVertextElementObject(&Vertext,indices,6);

  glClearColor(0.5f,0.9f,0.2f,0.1f);

  MONS_Event* Event;
  while (IsRunning)
  {

     glClear(GL_COLOR_BUFFER_BIT);
     MONS_PollWindowEvent(Window);
     Event = MONS_PopWindowEvent(Window);
     if (Event)
     {
       if (Event -> Type == MONSOON_EVENT_WINDOW_CLOSE)
       {
          IsRunning = False;
       }
     }

     glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
     MONS_SwapWindowDrawBuffers(Window);
     MONS_Sleep(50);
  }

  MONS_CloseWindow(Window);
  MONSTerminate();

  return 0;
}
