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
    if (FileHandle -> OSHandle == (void*)1)
    {
      LOG("Unable to open file %s",MONSOON_LOG_ERROR,1,FileHandle -> OSHandle);
      RemoveMemory(FileHandle -> FilePath);
      RemoveMemory(FileHandle);
    }
  #endif

  return FileHandle;
}

int MONS_WriteFile(MONS_File* FileHandle,char* Buffer,uint64_t Length)
{
  #ifdef _WIN32
    MONS_Win32_WriteFile(FileHandle -> OSHandle,Buffer,Length);
  #endif

  #ifndef MONSOON_DONT_LOG
    #ifdef MONSON_DEBUG
      LOG(
        "MONS_WriteFile: File=%s,Length=%llu",
        MONSOON_LOG_DEBUG,
        255,
        FileHandle -> FilePath,
        Length
      );
    #endif
  #endif
}

char* MONS_FullFilePath(char* FilePath)
{
  char* Path = GetMemory(MAX_PATH);
  if (Path)
  {
    Error_Memory();
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
