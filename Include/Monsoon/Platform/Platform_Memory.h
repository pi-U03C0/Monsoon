#ifndef MONS_PLATFORM_MEMORY_H
#define MONS_PLATFORM_MEMORY_H

#include "Monsoon/MONS_Types.h"

// Get Raw Memory From The System/OS
void* MONS_SystemGetMemory(size_t size);

// Get Raw
MSBool MONS_SystemRemoveMemory(void* memory,uint64_t);

#endif
