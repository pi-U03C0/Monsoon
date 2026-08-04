#ifndef MONSOON_UTILS_STRING_H
#define MONSOON_UTILS_STRING_H

#define GET_SPLIT_SIZE(text) ((long long)(text-1)[0])

#include <Monsoon/MONS_Types.h>

char** MONS_SplitString(char* text,char on);

char* MONS_AddString(char* fires,char* toadd);

char* MONS_IntToString(int num);

int MONS_StringToInt(char* text);

MSBool MONS_FindInString(char* text,char on);

#endif
