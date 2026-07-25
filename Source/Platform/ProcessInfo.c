#include <Monsoon/SystemHeaders.h>
#include <Monsoon/Monsoon.h>
#include <processthreadsapi.h>

char* MONS_GetCurrentWorkingDirectory()
{
  #ifdef _WIN32
    char* directory = (char*)GetMemory(1024);
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

void* MONS_GetProcAddress(char* ProcName)
{
  #ifdef _WIN32
    return GetProcAddress(NULL,ProcName);
  #endif
}
