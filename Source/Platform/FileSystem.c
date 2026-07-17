#include "Monsoon/Platform/Platform.h"
#include <Monsoon/Monsoon.h>

#include <stdlib.h>
#include <string.h>

MONS_File* MONS_OpenFile(char* FilePath,char Mode)
{
  LOG("FilePath=%s,Mode=%d",MONSOON_LOG_DEBUG,255,FilePath,Mode);
  LOG("Opening File %s for %s",MONSOON_LOG_INFO,3,FilePath,MONS_OpenModeToString(Mode));

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
          LOG("Unable to Open file %s %d",MONSOON_LOG_ERROR,1,FileHandle -> FilePath,GetLastError());
      #endif

      RemoveMemory(FileHandle -> FilePath);
      RemoveMemory(FileHandle);
    }
  #endif

  FileHandle -> FileSize = MONS_GetFileSize(FileHandle);

  LOG("Open File %s for %s",MONSOON_LOG_SUCCESS,2,FileHandle -> FilePath,MONS_OpenModeToString(Mode));

  return FileHandle;
}

MSBool MONS_CloseFile(MONS_File* FileHandle)
{
  MSBool dSucced;

  #ifdef _WIN32
    dSucced = MONS_Win32_CloseFile(FileHandle -> OSHandle);
  #endif

  if (!dSucced)
  {
    LOG("Unable to Close File %s",MONSOON_LOG_DEBUG,2,FileHandle -> FilePath);
    return False;
  }

  LOG("Close File %s Succfully",MONSOON_LOG_SUCCESS,1,FileHandle -> FilePath);

  RemoveMemory(FileHandle);
  return dSucced;
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

uint64_t MONS_ReadFile(MONS_File* FileHandle,char* Buffer,uint64_t Length)
{
  uint64_t len = 0;
  if (!Buffer)
  {
    #if MONSOON_LOG_LEVEL >= MONSOON_LOG_ERROR
       LOG("Buffer was NULL",MONSOON_LOG_ERROR,1);
    #endif

    return 0;
  }

  #ifdef _WIN32
    len = MONS_Win32_ReadFile(FileHandle -> OSHandle,Buffer,Length);
  #endif

  LOG("Readed %llu from File %s,When reading %llu",MONSOON_LOG_INFO,2,len,FileHandle -> FilePath,Length);

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

char* MONS_OpenModeToString(char Mode)
{
  switch (Mode)
  {
    case (MONSOON_FILE_READ):return "Read";
    case (MONSOON_FILE_WRITE):return "Write";
    case (MONSOON_FILE_READ_WRITE):return "Read&Write";
    default:return "?";
  }
}
