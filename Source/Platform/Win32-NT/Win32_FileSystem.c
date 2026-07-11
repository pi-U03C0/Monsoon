#include "Monsoon/MONS_Log.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

DWORD MONS_ModeToWin32Mode(char Mode)
{
  switch (Mode)
  {
    case MONSOON_MODE_READ:return GENERIC_READ;
    case MONSOON_MODE_WRITE:return GENERIC_WRITE;
    default:return 0;
  }
}

HANDLE MONS_Win32_OpenFile(char* FilePath,char Mode)
{
  DWORD wMode = MONS_ModeToWin32Mode(Mode);
  if (!wMode)
  {
    LOG("Invalid OpenFile Mode %d",MONSOON_LOG_ERROR,1,Mode);
    return 0;
  }

  HANDLE hFile = CreateFileA(
    FilePath,
    GENERIC_WRITE,
    NULL,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  if (hFile == INVALID_HANDLE_VALUE)
  {
    return (void*)1;
  }

  return hFile;
}

int MONS_Win32_WriteFile(HANDLE FileHandle,char* Buffer,int Length)
{
  LPDWORD WriteLen = 0;

  WriteFile(
    FileHandle,
    Buffer,
    Length,
    WriteLen,
    NULL
  );

  return *WriteLen;
}
