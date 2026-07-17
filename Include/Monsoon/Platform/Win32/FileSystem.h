#ifndef MONSOON_PLATFORM_WIN32_FILESYSTEM
#define MONSOON_PLATFORM_WIN32_FILESYSTEM

#include <Monsoon/MONS_Types.h>

#define MONSOON_MODE_READ 1
#define MONSOON_MODE_WRITE 2
#define MONSOON_MODE_READ_WRITE 3


HANDLE MONS_Win32_OpenFile(char* FilePath,char Mode);
int MONS_Win32_WriteFile(HANDLE FileHandle,char* Buffer,int Length);

char* Win32_GetError();

#endif
