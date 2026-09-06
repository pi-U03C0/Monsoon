#include <stdio.h>
#define INCLUDE_STD
#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

int main(int argc, char** argv)
{
  MSBool IsRunning = True;

  if (!MONSInit(NULL, MONSOON_LOG_INFO))
  {
    printf("Unable to Init Monsoon\n");
    return 1;
  }

  MONS_Window* Window = MONS_CreateWindow("Monsoon: Test Window", &(MONS_Rect){100,100,400,400});
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);
  MONS_Event* Event = NULL;
  while (IsRunning)
  {
    MONS_PollWindowEvent(Window);
    Event = MONS_PopWindowEvent(Window);
    if (Event)
    {
      printf("Event.Type = %llu\n",Event -> Type);
      if (Event -> Type == MONSOON_EVENT_WINDOW_CHANGE_SIZE)
      {
        printf("MONSOON_EVENT_WINDOW_CHANGE_SIZE:new Hight=%d,Wigh=%d\n",((MONS_WindowPrarmSize*)Event -> Prarms) -> Height,((MONS_WindowPrarmSize*)Event -> Prarms) -> Width);
      }
      if (Event -> Type == MONSOON_EVENT_WINDOW_MOVE)
      {
        printf("MONSOON_EVENT_WINDOW_MOVE: new X=%d,Y=%d\n",((MONS_WindowPrarmPosition*)Event -> Prarms) -> X,((MONS_WindowPrarmPosition*)Event -> Prarms) -> Y);
      }
      if (Event -> Type == MONSOON_EVENT_KEY_DOWN)
      {
        printf("MONSOON_EVENT_KEY_DOWN: new Key = %c(%d)\n",((MONS_WindowPrarmKey*)Event -> Prarms) -> Key,((MONS_WindowPrarmKey*)Event -> Prarms) -> Key);
        if (((MONS_WindowPrarmKey*)Event -> Prarms) -> Key == '')
        {
          IsRunning = False;
        }
      }
      if (Event -> Type == MONSOON_EVENT_WINDOW_CLOSE)
      {
        IsRunning = False;
      }
      FreeEvent(Event);
    }
  }
  return 0;
}
