#define FILE_INDEX_NOT_EMBED

#include <stdio.h>
#include <stdlib.h>

#include <Monsoon/Monsoon.h>

#include <Monsoon/SystemHeaders.h>

uint64_t MONS_GetErrorCode(char* MessageBuffer)
{
  if (MessageBuffer != NULL)
  {
  }

  return __Monsoon -> Error.Code;
}

void MONS_SetErrorCode(uint16_t ErrorLine,uint16_t ErrorFile,uint16_t ErrorProjectPart,uint16_t ErrorReason)
{
  __Monsoon -> Error.Code = EnCodeError(ErrorLine, ErrorFile, ErrorProjectPart, ErrorReason);
  __Monsoon -> Error.Message = MONS_GetErrorMessage(__Monsoon -> Error.Code);
}

char* MONS_GetErrorMessage(uint64_t Code)
{
  MONSError* DeCode = DeCodeError(Code);
  char* File =  MONS_SearchErrorFile(DeCode -> SourceFile);
  char* ErrorMessage = MONS_SearchErrorMessage(DeCode -> ErrorReason,DeCode -> ProjectPart);
  int i = snprintf(NULL, 0, "Monsoon Error(%020llu): %s at %s(%d):%d",Code,ErrorMessage,File,DeCode -> SourceFile,DeCode -> ErrorLine);
  char* buffer = malloc(i);
  if (!buffer)return NULL;
  snprintf(buffer,i+1, "Monsoon Error(%020llu): %s at %s(%d):%d",Code,ErrorMessage,File,DeCode -> SourceFile,DeCode -> ErrorLine);
  return buffer;
}

uint64_t EnCodeError(uint16_t ErrorLine, uint16_t SourceFile, uint16_t ProjectPart, uint16_t ErrorReason)
{
  uint64_t ErrorCode = 0;
  ErrorCode = ErrorReason;
  ErrorCode *= 100000ULL;

  ErrorCode += ProjectPart;
  ErrorCode *= 100000ULL;

  ErrorCode += SourceFile;
  ErrorCode *= 100000ULL;

  ErrorCode += ErrorLine;

  return ErrorCode;
}

MONSError* DeCodeError(uint64_t Code)
{
   MONSError* ErrorObject = malloc(sizeof(MONSError));
   ErrorObject -> Code = Code;

   uint64_t ErrorCode = Code;

   ErrorObject -> ErrorLine = ErrorCode % 100000ULL;
   ErrorCode /= 100000ULL;

   ErrorObject -> SourceFile = ErrorCode % 100000ULL;
   ErrorCode /= 100000ULL;

   ErrorObject -> ProjectPart = ErrorCode % 100000ULL;
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

    snprintf(FilePath, 1024, "%s/FileIndex.txt",CurrentDirectory);

    if (!MONS_FileExists(FilePath))
    {
      MONS_Log(
        "Index File does not Exists At \"%s\"",
        Make_Code(1),
        MONSOON_LOG_ERROR
      );
      return NULL;
    }
    MONS_File* hFile = MONS_OpenFile();
  #else
  #endif

  return FilePath;
}

char* MONS_SearchErrorFile(uint16_t SourceFile)
{
  return NULL;
}

char* MONS_SearchErrorMessage(uint16_t ErrorReason,uint16_t ProjectPart)
{

}

char* MONS_SeverityToString(char Severity)
{
  switch (Severity)
  {
    case MONSOON_LOG_ERROR:return "ERROR";
    case MONSOON_LOG_CRITICAL:return "CRITICAL";
    case MONSOON_LOG_FATAL:return "FATAL";
    case MONSOON_LOG_INFO:return "INFO";
    case MONSOON_LOG_SUCCESS:return "SUCCESS";
    case MONSOON_LOG_WARNING:return "WARNING";
    default:return "?";
  }
}
