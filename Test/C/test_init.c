#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#define INCLUDE_STD
#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

int main(int argc, char** argv)
{
  if (!MONSInit(
    MakeInit_Flags(Component(MONSOON_COMPONENT_OPENGL)),
    MONSOON_LOG_DEBUG
  ))
  {
     MONS_WriteStdOutput("MONSInit filed\n",15);
     return 1;
  }
  printf("Version = %llu\n",MONS_GetVersion());

  MONSTerminate();

  return 0;
}
