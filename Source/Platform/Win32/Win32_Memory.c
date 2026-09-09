#include <windows.h>

#include "Monsoon/MONS_Types.h"
#include "Monsoon/Platform/Win32/Memory.h"

void* MONS_Win32_GetMemory(uint64_t MemorySize)
{
  HANDLE HeapHandle = GetProcessHeap();
  if (!HeapHandle) return NULL;
  return HeapAlloc(HeapHandle, 0,MemorySize);
}

MSBool MONS_Win32_RemoveMemory(void *AllocPointer, uint64_t AllocSize)
{
  return False;
}
