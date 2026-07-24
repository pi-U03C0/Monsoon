#ifndef MONSOON_ERROR_H
#define MONSOON_ERROR_H

#include <Monsoon/MONS_Types.h>

#define Make_Code(ErrorReason) EnCodeError(__LINE__,__FILE_NUMBER__,__PROJECT_PART__,ErrorReason)
#define Error_Memory() \
     LOG("Memory Error",MONSOON_LOG_CRITICAL,100);\
     MONS_SetErrorCode(Make_Code(100))


uint64_t MONS_GetErrorCode(char* Message);

//Set the gloable Error
void MONS_SetErrorCode(uint64_t Code);

//Convert the line,source,project,reason to one number
uint64_t EnCodeError(uint16_t ErrorLine, uint16_t SourceFile, uint16_t ProjectPart, uint16_t ErrorReason);

//convert the code to a message
char* MONS_GetErrorMessage(uint64_t ErrorCode);

MONSError* DeCodeError(uint64_t Code);

char* MONS_SearchErrorFile(uint16_t SourceFile);

char* MONS_SearchErrorMessage(uint16_t ErrorReason,uint16_t ProjectPart);

char* MOND_ReadAndParserFileIndex();

#endif
