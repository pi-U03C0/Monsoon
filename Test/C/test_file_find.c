#include "Monsoon/MONS_Init.h"
#include <Monsoon/Monsoon.h>

int main(int argc, char** argv)
{
  if (!MONSInit(NULL, MONSOON_LOG_DEBUG))
  {
    return 1;
  }











  MONS_AddSearchPath("c:/Users/dell/.python313/Python/Python313/Lib/asyncio/__pycache__/__pycache__");
  MONS_AddSearchPath("c:/Users/dell/.python313/Python/Python313/Lib/asyncio/__pycache__");



  MONS_FindFile("jdj","ddd",False);
  MONSTerminate();
  return 0;
}
