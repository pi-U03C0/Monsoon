#ifndef MONSOON_PLATFORM_LIBRARY_H
#define MONSOON_PLATFORM_LIBRARY_H

#include <Monsoon/MONS_Types.h>

#define MONSOON_LIBRARY_LIMIT 10

MONS_DynamicLibrary* MONS_LoadLibrary(char* DLLPath,uint16_t LoadFlags);

MSBool MONS_FreeLibrary(MONS_DynamicLibrary* Library);

//Get a Function Address
void* MONS_GetProcAddress(const char* ProcName,MONS_DynamicLibrary* Library);


#endif
