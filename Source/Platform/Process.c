#include "Monsoon/MONS_Error.h"
#define INCLUDE_STD

#include <Monsoon/SystemHeaders.h>
#include <Monsoon/Monsoon.h>

char* MONS_GetCurrentWorkingDirectory()
{
  #ifdef MONSOON_PLATFORM_NT
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
  #ifdef MONSOON_PLATFORM_NT
    return GetProcessId(NULL);
  #endif
}

char* MONS_GetEnvironmentVariable(char* Name)
{
  char* envBuffer = NULL;
  #ifdef MONSOON_PLATFORM_NT
    uint32_t envLenght = GetEnvironmentVariableA(Name,envBuffer,0);
    if (!envLenght)
    {
       return NULL;
    }

    envBuffer = GetMemory(envLenght+1);
    if (!envBuffer)
    {
       Error_Memory();
       return NULL;
    };

    GetEnvironmentVariableA(Name, envBuffer, envLenght);
  #endif

  #ifdef MONSOON_PLATFORM_POSIX
    char* envFilePath = GetMemory(1024);
    if (!envFilePath)
    {
       Error_Memory();
       return NULL;
    }

    snprintf(envFilePath,1024,"/proc/%d/environ",MONS_GetProcessId());
    MONS_File* envFile = MONS_OpenFile(envFilePath,MONSOON_FILE_READ);

    char* rBuffer = GetMemory(envFile -> FileSize);
    if (!rBuffer)
    {
      RemoveMemory(envFilePath);
      Error_Memory();
      return NULL;
    }

    MONS_ReadFile(envFile,rBuffer,envFile -> FileSize);
    MONS_SplitString(rBuffer, 0);
    RemoveMemory(rBuffer);
    MONS_CloseFile(envFile);

  #endif

  return envBuffer;
}
