#ifndef WIN32_MEMORY_H
#define WIN32_MEMORY_H

#include <Monsoon/Monsoon.h>

MONS_API void* MONS_Win32_GetMemory(uint64_t AllocSize);
MONS_API MSBool MONS_Win32_RemoveMemory(void* AllocPointer,uint64_t AllocSize);

#endif
