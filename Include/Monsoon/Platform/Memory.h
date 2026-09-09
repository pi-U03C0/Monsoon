#ifndef MONSOON_MEMORY_H
#define MONSOON_MEMORY_H

#include "Monsoon/MONS_Types.h"
#include <stddef.h>


// Alloc Memory
void* MONS_AllocMemory(size_t size);

//DeAlloc Memory
MSBool MONS_DeAllocMemory(void* memory);

//Dups Memory return a Copy
void* MONS_DupeMemory(char* Memory,uint64_t Size);

// Get Raw Memory From The System/OS
void* MONS_SystemGetMemory(size_t size);

MSBool MONS_SystemRemoveMemory(void* memory,uint64_t);

#endif
