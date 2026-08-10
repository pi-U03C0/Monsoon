#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#define INCLUDE_STD
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
  printf("version = %llu\n",MONS_GetVersion());

  MONSTerminate();

  return 0;
}
