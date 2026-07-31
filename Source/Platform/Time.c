#include <Monsoon/MONS_Types.h>
#include <Monsoon/SystemHeaders.h>

void MONS_Sleep(uint32_t Milliseconds)
{
  #ifdef _WIN32
    Sleep(Milliseconds);
  #endif
}
