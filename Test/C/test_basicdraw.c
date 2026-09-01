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

  MONSTerminate();
  return 0;
}
