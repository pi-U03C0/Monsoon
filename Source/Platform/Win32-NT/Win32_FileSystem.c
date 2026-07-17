#include "Monsoon/Platform/Win32/FileSystem.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

DWORD MONS_ModeToWin32Mode(char Mode)
{
  switch (Mode)
  {
    case MONSOON_MODE_READ:return GENERIC_READ;
    case MONSOON_MODE_WRITE:return GENERIC_WRITE;
    case MONSOON_MODE_READ_WRITE:return GENERIC_WRITE|GENERIC_READ;
    default:return 0;
  }
}

MSBool MONS_Win32_MakeFile(char* FilePath)
{
  HANDLE hFile =  CreateFileA(
    FilePath,
    0,
    0,
    NULL,
    CREATE_NEW,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  if (hFile == INVALID_HANDLE_VALUE)
  {
    return False;
  }
  return CloseHandle(hFile);
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
    wMode,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  if (hFile == INVALID_HANDLE_VALUE)
  {
    return NULL;
  }

  return hFile;
}

int MONS_Win32_WriteFile(HANDLE FileHandle,char* Buffer,int Length)
{
  DWORD WriteLen = 0;

  WriteFile(
    FileHandle,
    Buffer,
    Length,
    &WriteLen,
    NULL
  );

  return WriteLen;
}

int MONS_Win32_ReadFile(HANDLE FileHandle,char* Buffer,int Length)
{
   DWORD ReadLen = 0;
   ReadFile(
      FileHandle,
      Buffer,
      Length,
      &ReadLen,
      NULL
   );

   return ReadLen;
}

char* Win32_GetError()
{
  switch (GetLastError())
  {
    default:
    {
      return "?";
    }
  }

}
