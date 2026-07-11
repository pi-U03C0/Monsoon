#include <Monsoon/SystemHeaders.h>

#include <stdlib.h>

#include <Monsoon/Monsoon.h>

char* MONS_GetCurrentWorkingDirectory()
{
  #ifdef _WIN32
    char* directory = (char*)GetMemory(1024);
    GetCurrentDirectoryA(1024,directory);
    return directory;
  #endif
}
