#define FILE_INDEX_NOT_EMBED
#define INCLUDE_STD

#include <Monsoon/Monsoon.h>

#include <Monsoon/SystemHeaders.h>

uint64_t MONS_GetErrorCode()
{
  return __Monsoon -> Error.Code;
}

void MONS_SetErrorCode(uint64_t Code)
{
  __Monsoon -> Error.Code = Code;
}

uint64_t EnCodeError(uint16_t ErrorLine, uint16_t SourceFile, uint16_t ErrorReason)
{
  uint64_t ErrorCode = 0;
  ErrorCode = ErrorReason;
  ErrorCode *= 100000ULL;

  ErrorCode += SourceFile;
  ErrorCode *= 100000ULL;

  ErrorCode += ErrorLine;

  return ErrorCode;
}

MONSError* DeCodeError(uint64_t Code)
{
   MONSError* ErrorObject = GetMemory(sizeof(MONSError));
   ErrorObject -> Code = Code;

   uint64_t ErrorCode = Code;

   ErrorObject -> ErrorLine = ErrorCode % 100000ULL;
   ErrorCode /= 100000ULL;

   ErrorObject -> SourceFile = ErrorCode % 100000ULL;
   ErrorCode /= 100000ULL;

   ErrorObject -> ErrorReason = ErrorCode % 100000ULL;

   return ErrorObject;
}

char* MOND_ReadAndParserFileIndex()
{
  char* buffer = NULL;
  #ifdef FILE_INDEX_NOT_EMBED
    char* FilePath = (char*)GetMemory(1024);
    char* CurrentDirectory = MONS_GetCurrentWorkingDirectory();

    if (!CurrentDirectory) return NULL;

    snprintf(FilePath, 1024, "%s/"MONSOON_FILE_INDEX_NAME,CurrentDirectory);

    if (!MONS_FileExists(FilePath))
    {
      LOG(
        "Index File does not Exists At \"%s\"",
        MONSOON_LOG_ERROR,
        1,
        FilePath
      );
      return NULL;
    }
    MONS_File* hFile = MONS_OpenFile(FilePath,MONSOON_FILE_READ);
    buffer = GetMemory(hFile -> FileSize);
    MONS_ReadFile(hFile, buffer, hFile -> FileSize);
  #endif

  return FilePath;
}

char* MONS_SearchErrorFile(uint16_t SourceFile)
{
  MOND_ReadAndParserFileIndex();

  return NULL;
}

