#include "Monsoon/Graphic/API/OpenGL/Context.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

int main(int argc, char** argv)
{
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

  MONS_
  MONS_RegisterBasicDrawWindow(Window)

  MONSTerminate();
  return 0;
}
