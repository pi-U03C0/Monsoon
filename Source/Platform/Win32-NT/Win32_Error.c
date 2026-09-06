#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

uint64_t MONS_Win32_GetErrorCode()
{
  return GetLastError();
}

MSBool MONS_Win32_IsHandleValid(void* Handle)
{
  if (GetHandleInformation(Handle,NULL))
  {
    return True;
  }

  return False;
}
