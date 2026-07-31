#include <Monsoon/SystemHeaders.h>
#include <Monsoon/Monsoon.h>

char* MONS_GetCurrentWorkingDirectory()
{
  #ifdef _WIN32
    char* directory = (char*)GetMemory(1024);
    if (!directory)
    {
      Error_Memory();
      return NULL;
    }
    GetCurrentDirectoryA(1024,directory);
    return directory;
  #endif
}

uint32_t MONS_GetProcessId()
{
  #ifdef _WIN32
    return GetProcessId(NULL);
  #endif
}

void* MONS_GetProcAddress(const char* ProcName)
{
  #ifdef _WIN32
     void* address = NULL;
     static HMODULE MONS_Module;

     if (!MONS_Module)
     if (!GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCSTR)&MONS_GetProcAddress,
        &MONS_Module
     ))
     {
       LOG("Unable to get Module Handle for Monsoon",MONSOON_LOG_CRITICAL,MONSOON_LOG_UNABLE_GET);
       return NULL;
     }

     address = GetProcAddress(MONS_Module,ProcName);
     if (address)return address;
     address = GetProcAddress(GetModuleHandleA(NULL), ProcName);

     return address;
  #endif
}
