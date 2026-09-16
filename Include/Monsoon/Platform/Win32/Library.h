#ifndef MONSOON_PLATFORM_WIN32_LIBRARY_H

#include <Monsoon/SystemHeaders.h>
#include <Monsoon/Monsoon.h>

//--------------------------------------------------------------------------
//`Load` a DynamicLibrary(*.DLL) PE32/PE32+ Library File Useing Natiive NT APIs
//-Parameters-----------------------------------------------------------------
//`DLLPath`:The Path to the DLL File to Load
//-Return---------------------------------------------------------------------
//`Retuns` the NT Handle to the Loaded ModuleHandle of the DLL,Null on Errors
//---------------------------------------------------------------------------
MONS_API HANDLE MONS_Win32_LoadLibrary(char* DLLPath);

MONS_API void* MONS_Win32_GetProcAddress(const char* ProcName,HMODULE ModuleHandle);

MONS_API MSBool MONS_Win32_FreeLibrary(HANDLE LibraryHandle);

#endif
