#include "Monsoon/Graphic/Render/BasicDraw/Rectangle.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(
    MakeInit_ComponentsOption(MONSOON_COMPONENT_BASICDRAW),
    MONSOON_LOG_DEBUG
  ))
  {
    return 1;
  }

  MONS_Window* Window = MONS_CreateWindow(
    "Monsoon test: test_basicdraw",
    (MONS_Rect){
      .X = 300,
      .Y = 100,
      .Height = 600,
      .Width = 600
    }
  );
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);

  uint8_t Context = MONS_CreateBasicDrawContext();
  MONS_RegisterBasicDrawWindow(Context,Window);
  MONS_LoadBasicDrawContextResources(Context);

  MONS_Event* Event;
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

    MONS_BasicDrawRectangle(Context, (MONS_Rect){100,100,100,100}, (MONS_Colour){100,100,100,255});
  }

  MONS_UnLoadBasicDrawContextResources(Context);
  MONS_UnRegisterBasicDrawWindow(Context);
  MONS_RemoveBasicDrawContext(Context);

  MONSTerminate();
  return 0;
}
