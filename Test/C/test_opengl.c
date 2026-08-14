#define INCLUDE_STD
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(MONSOON_INIT_OPENGL), MONSOON_LOG_DEBUG))
  {
    return 1;
  }

  int attributes[] =
  {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
      WGL_CONTEXT_MINOR_VERSION_ARB, 6,
      WGL_CONTEXT_PROFILE_MASK_ARB,
      WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0
  };

  MONS_Window* Window = MONS_CreateWindow("jj", &(MONS_Rect){100,100,10,100});
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);
  if (!Window)
  {
    printf("unable to open window");
    return 1;
  }
  MONS_OpenGLContext* Context = MONS_CreateOpenGLContext(Window, attributes);
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
