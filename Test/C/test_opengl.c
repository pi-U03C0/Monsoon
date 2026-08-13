#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  if (!MONSInit(MakeInit_ComponentsOption(MONSOON_INIT_OPENGL), MONSOON_LOG_DEBUG))
  {
    return 1;
  }

  MONS_WriteStdOutput((char*)glGetString(GL_VERSION));
  MONS_WriteStdOutput("\n");

  MONSTerminate();
  return 0;
}
