#ifndef MONSOON_ERROR_H
#define MONSOON_ERROR_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Monsoon.h>

#define Make_Code(ErrorReason) EnCodeError(__LINE__,__FILE_NUMBER__,ErrorReason)
#define Error_Memory() \
     LOG("Memory Error Unable to alloc Memory",MONSOON_LOG_FATAL,MONSOON_LOG_UNABLE_TO_ALLOC_MEMORY);\
     MONS_SetErrorCode(Make_Code(100))

MONS_API uint64_t MONS_GetErrorCode();

//Set the gloable Error
MONS_API void MONS_SetErrorCode(uint64_t Code);

//Convert the line,source,project,reason to one number
MONS_API uint64_t EnCodeError(uint16_t ErrorLine, uint16_t SourceFile, uint16_t ErrorReason) ;

//convert the code to a message
MONS_API char* MONS_GetErrorMessage(uint64_t ErrorCode);

MONS_API MONSError* DeCodeError(uint64_t Code);

MONS_API char* MONS_SearchErrorFile(uint16_t SourceFile);

MONS_API char* MONS_SearchErrorMessage(uint16_t ErrorReason,uint16_t ProjectPart);

MONS_API char* MONS_ReadAndParserFileIndex();

#endif
