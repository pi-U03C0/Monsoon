#include "Monsoon/Platform/Win32/Window.h"
#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

void printinfo()
{
  LOG("OnExit",MONSOON_LOG_INFO,0);
  LOG("MONS_GetVersion = %d",MONSOON_LOG_DEBUG,255,MONS_GetVersion());
}


int main(int argc, char** argv)
{
  MSBool IsRunning = True;
  if (!MONSInit(MakeInit_ComponentsOption(1,2),MONSOON_LOG_LEVEL))
  {
     MONS_WriteStdOutput("MONSInit filed\n");
     return 1;
  }

  MONS_Window* Window = MONS_CreateWindow("test", &(MONS_Rect){100,100,400,400}, WindowProc);
  MONS_ShoWindow(Window, MONS_SHOW_WINDOW);

  while (IsRunning)
  {
    MONS_WindowPollEvent(Window);
  }

  MONS_CloseWindow(Window);

  MONSTerminate();

  return 0;
}
