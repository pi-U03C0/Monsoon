#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

int main(int argc, char** argv)
{
  if (!MONSInit(
    MakeInit_ComponentsOption(MONSOON_INIT_OPENGL),
    MONSOON_LOG_DEBUG
  ))
  {
     MONS_WriteStdOutput("MONSInit filed\n");
     return 1;
  }

  MONSTerminate();

  return 0;
}
