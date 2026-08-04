#include <Monsoon/SystemHeaders.h>
#include <Monsoon/Monsoon.h>

HANDLE MONS_Win32_LoadLibrary(char* DLLPath)
{
   HMODULE Library = LoadLibraryExA(DLLPath,NULL,0);
   if (!Library)
   {
     return NULL;
   }
  return Library;
}

MSBool MONS_Win32_FreeLibrary(HANDLE LibraryHandle)
{
   #ifndef MONSOON_NO_LOG
      char DLLPath[MAX_PATH];
      GetModuleFileNameA(LibraryHandle,DLLPath,MAX_PATH);
      LOG("Freeing Library",MONSOON_LOG_INFO,MONSOON_LOG_FREE,DLLPath);
   #endif

   MSBool Success = FreeLibrary(LibraryHandle);
   return Success;
}

void* MONS_Win32_GetProcAddress(const char* ProcName,HMODULE ModuleHandle)
{
  void* address = NULL;
  //if ModuleHandle was pass in get the proc from there and return it
  if (ModuleHandle)
  {
    address = GetProcAddress(ModuleHandle,ProcName);
  }
  else
  {
    //get Monsoon ModuleHandle and get address from it
    HMODULE MONS_Module;
    if (!GetModuleHandleExA(
      GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
      (LPCSTR)&MONS_Win32_GetProcAddress,
      &MONS_Module
    ))
    {
      LOG("Unable to get Module Handle for Monsoon",MONSOON_LOG_CRITICAL,MONSOON_LOG_UNABLE_GET);
      return NULL;
    }

    address = GetProcAddress(MONS_Module,ProcName);
    //if address was not found get it from the exe
    if (!address)
    {
      MONS_Module = GetModuleHandleA(NULL);
      if (!MONS_Module)
      {
        return NULL;
      }
    }
    address = GetProcAddress(MONS_Module,ProcName);
  }
  return address;
}
