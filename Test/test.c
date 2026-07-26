#include "Monsoon/MONS_Window.h"
#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(1,2),MONSOON_LOG_LEVEL))
  {
     MONS_WriteStdOutput("MONSInit filed\n");
     return 1;
  }

  MONS_Window* Window = MONS_CreateWindow("test", &(MONS_Rect){100,100,400,400});
  MONS_ShoWindow(Window, MONS_SHOW_WINDOW);

  MONS_Event* Event = NULL;
  while (IsRunning)
  {
    MONS_WindowPollEvent(Window);
    Event = MONS_PopWindowEvent(Window);

    if (Event)
    {
      if (Event -> Type == MONSOON_EVENT_QUIT) IsRunning = False;
    }
  }

  MONS_CloseWindow(Window);

  MONSTerminate();

  return 0;
}
