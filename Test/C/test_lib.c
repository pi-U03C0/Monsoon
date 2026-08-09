//*D(test_dll),*
#include <Monsoon/Monsoon.h>

int main(int argc, char** argv)
{
  if (!MONSInit(NULL, MONSOON_LOG_DEBUG))
  {
    return 1;
  }

  MONS_DynamicLibrary* Library = MONS_LoadLibrary("test_dll.dll", 0);
  MONS_GetProcAddress("test__", Library);

  MONSTerminate();
  return 0;
}
