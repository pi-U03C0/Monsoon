#include <windows.h>

#include "Monsoon/MONS_Types.h"

void* MONS_Win32_GetMemory(uint64_t MemorySize)
{
  HANDLE HeapHandle = GetProcessHeap();
  if (!HeapHandle) return NULL;
  return HeapAlloc(HeapHandle, 0,MemorySize);
}
