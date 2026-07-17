#ifndef MONSOON_ERROR_H
#define MONSOON_ERROR_H

#include <Monsoon/MONS_Types.h>

#define Make_Code(ErrorReason) EnCodeError(__LINE__,__FILE_NUMBER__,__PROJECT_PART__,ErrorReason)
#define Error_Memory()

uint64_t MONS_GetErrorCode(char* Message);

void MONS_SetErrorCode(uint64_t Code);

uint64_t EnCodeError(uint16_t ErrorLine, uint16_t SourceFile, uint16_t ProjectPart, uint16_t ErrorReason);

char* MONS_GetErrorMessage(uint64_t ErrorCode);

uint64_t EnCodeError(uint16_t ErrorLine, uint16_t SourceFile, uint16_t ProjectPart, uint16_t ErrorReason);

MONSError* DeCodeError(uint64_t Code);

char* MONS_SearchErrorFile(uint16_t SourceFile);

char* MONS_SearchErrorMessage(uint16_t ErrorReason,uint16_t ProjectPart);

char* MONS_SeverityToString(char Severity,MSBool Colour);

#endif
