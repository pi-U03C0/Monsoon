#define INCLUDE_STD
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(MONSOON_INIT_OPENGL), MONSOON_LOG_INFO))
  {
    return 1;
  }

  MONS_Window* Window = MONS_CreateWindow("Monsoon: OpenGL Clear Window test", &(MONS_Rect){200,200,600,600});
  if (!Window)
  {
    printf("unable to open window\n");
    return 1;
  }
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);

  MONS_OpenGLContext* Context = MONS_CreateOpenGLContext(Window, NULL);
  if (!MONS_MakeCurrentOpenGLContext(Context))
  {
    printf("could not set opengl context as currre\n");
    return 1;
  }

  glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

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
      FreeEvent(Event);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    MONS_SwapWindowDrawBuffers(Window);
  }

  MONS_CloseWindow(Window);

  MONSTerminate();

  return 0;
}
