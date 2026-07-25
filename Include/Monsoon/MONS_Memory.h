#ifndef MONSOON_MEMORY_H
#define MONSOON_MEMORY_H

#include "Monsoon/MONS_Types.h"
#include <stddef.h>

struct MONS_Memory {
  size_t size;
  void* memory;
};
typedef struct MONS_Memory MONS_Memory ;

// Alloc Memory
void* MONS_AllocMemory(size_t size);

//DeAlloc Memory
MSBool MONS_DeAllocMemory(void* memory);

//Dups Memory return a Copy
void* MONS_DupeMemory(char* Memory,uint64_t Size);

#endif
