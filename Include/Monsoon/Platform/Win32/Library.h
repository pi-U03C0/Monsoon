#ifndef MONSOON_PLATFORM_WIN32_LIBRARY_H

#include <Monsoon/SystemHeaders.h>
#include <Monsoon/MONS_Types.h>


HANDLE MONS_Win32_LoadLibrary(char* DLLPath);

void* MONS_Win32_GetProcAddress(const char* ProcName,HMODULE ModuleHandle);

MSBool MONS_Win32_FreeLibrary(HANDLE LibraryHandle);

#endif
