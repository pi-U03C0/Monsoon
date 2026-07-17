#include "Monsoon/MONS_FileSystem.h"
#include <Monsoon/Monsoon.h>
#include <stdlib.h>
#include <string.h>

MONS_File* MONS_OpenFile(char* FilePath,char Mode)
{
  MONS_File* FileHandle = GetMemory(sizeof(MONS_File));
  if (!FileHandle)
  {
    Error_Memory();
    return NULL;
  }
  FileHandle -> FilePath = MONS_FullFilePath(FilePath);

  #ifdef _WIN32
    FileHandle -> OSHandle = MONS_Win32_OpenFile(FileHandle -> FilePath, Mode);
    if (FileHandle -> OSHandle == NULL)
    {
      #if MONSOON_LOG_LEVEL >= MONSOON_LOG_ERROR
          LOG("Unable to Open file %s ",MONSOON_LOG_ERROR,1,FileHandle -> OSHandle);
      #endif

      RemoveMemory(FileHandle -> FilePath);
      RemoveMemory(FileHandle);
    }
  #endif


  return FileHandle;
}

int MONS_WriteFile(MONS_File* FileHandle,char* Buffer,uint64_t Length)
{
  int len = 0;

  #ifdef _WIN32
    len = MONS_Win32_WriteFile(FileHandle -> OSHandle,Buffer,Length);
  #endif

  #if MONSOON_LOG_LEVEL >= MONSOON_LOG_DEBUG
    LOG(
      "File=%s,Length=%llu",
      MONSOON_LOG_DEBUG,
      255,
      FileHandle -> FilePath,
      Length
    );
  #endif

  FileHandle -> FileSize = MONS_GetFileSize(FileHandle -> OSHandle);

  return len;
}

char* MONS_FullFilePath(char* FilePath)
{
  char* Path = GetMemory(MAX_PATH);
  if (!Path)
  {
    Error_Memory();
    return NULL;
  }
  #ifdef _WIN32
    GetFullPathNameA(
      FilePath,
      MAX_PATH,
      Path,
      NULL
    );
  #endif
  #if defined(__linux__)
    realpath(FilePath,Path);
  #endif

  return Path;
}

inline MSBool MONS_FileExists(char* FilePath)
{
  #ifdef _WIN32
    return PathFileExistsA(FilePath);
  #endif
}

inline uint64_t MONS_GetFileSize(MONS_File* hFile)
{
  #ifdef _WIN32
    return GetFileSize(hFile -> OSHandle,NULL);
  #endif
}


