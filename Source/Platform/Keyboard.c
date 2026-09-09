#include <Monsoon/Monsoon.h>
#include <stdint.h>

MSBool MONS_IsKeyDown(uint32_t Key)
{
  #ifdef MONSOON_PLATFORM_NT
    MONS_Win32_IsKeyDown(Key);
  #endif

  return False;
}

