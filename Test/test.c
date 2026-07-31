#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>
#include <windows.h>
#include <stdio.h>

MONS_Window* Window = NULL;

BOOL WINAPI PrintQueue(DWORD CtrlType)
{
  switch (CtrlType)
  {
    case CTRL_C_EVENT:
    {
       MONS_PrintQueue(Window -> Events);
    }
  }
  ExitProcess(0);
}

int main(int argc, char** argv)
{
  SetConsoleCtrlHandler(PrintQueue,True);
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(1),MONSOON_LOG_INFO))
  {
     MONS_WriteStdOutput("MONSInit filed\n");
     return 1;
  }

  Window = MONS_CreateWindow("test", &(MONS_Rect){100,100,400,400});
  if (!Window) return 2;
  MONS_ShoWindow(Window, MONS_SHOW_WINDOW);

  MONS_Event* Event = NULL;
  while (IsRunning)
  {
    MONS_PollWindowEvent(Window);
    Event = MONS_PopWindowEvent(Window);
    if (Event)
    {
      if (Event -> Type == MONSOON_EVENT_QUIT || Event -> Type == MONSOON_EVENT_WINDOW_CLOSE)
      {
        IsRunning = False;
        MONS_WriteStdOutput("IsRunning is closed\n");
      }
    }
    MONS_Sleep(100);
  }
  MONS_CloseWindow(Window);

  MONSTerminate();

  return 0;
}
