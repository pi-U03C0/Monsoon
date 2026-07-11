#ifndef WIN32_MEMORY_H
#define WIN32_MEMORY_H

#include "Monsoon/MONS_Types.h"

void* MONS_Win32_GetMemory(uint64_t AllocSize);
MSBool MONS_Win32_RemoveMemory(void* AllocPointer,uint64_t AllocSize);

#endif
