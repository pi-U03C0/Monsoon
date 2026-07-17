#include <Monsoon/Monsoon.h>

#include <Monsoon/SystemHeaders.h>

void* MONS_AllocMemory(size_t size)
{
  MONS_Memory* system_memory = (MONS_Memory*)MONS_SystemGetMemory(sizeof(size_t)+size);
  if (!system_memory)
  {
    return NULL;
  }

  return system_memory -> memory;
}

MSBool MONS_DeAllocMemory(void* memory)
{
  MONS_Memory* system_memory = memory;
  return MONS_SystemRemoveMemory(system_memory -> memory,system_memory -> size);
}

void* MONS_SystemGetMemory(size_t size)
{
  #ifdef _WIN32
    return MONS_Win32_GetMemory(size);
  #endif
}

MSBool MONS_SystemRemoveMemory(void* memory,uint64_t size)
{
  #ifdef _WIN32
      return MONS_Win32_RemoveMemory(memory,size);
  #endif
}
