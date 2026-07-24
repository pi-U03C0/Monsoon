#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

uint64_t MONS_Win32_GetErrorCode()
{
  return GetLastError();
}
