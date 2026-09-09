#include <Monsoon/Monsoon.h>
#include <windows.h>

MSBool MONS_Win32_IsKeyDown(uint32_t Key)
{
  return GetAsyncKeyState(Key);
}
