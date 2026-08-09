#ifndef MONSOON_UTILS_STRING_H
#define MONSOON_UTILS_STRING_H

#define GET_SPLIT_SIZE(text) ((unsigned long long)(text-1)[0])

#include <Monsoon/MONS_Types.h>

//Split a String with on
//---------------------------------------------------
//`text`:The Text to Split
//`on`:What to split on
//---------------------------------------------------
//`The` Return Split String array Length is one address before the address that was return
//`For` Example if the return address was 0x1000001 than the Length will be at 0x1000000
//`All` version of the function come with a macro called GET_SPLIT_SIZE to get the Length
char** MONS_SplitString(char* text,char on);

char* MONS_FindAndReplaceString(char* Original,char* Find,char* Replace);

//Compone two string
char* MONS_AddString(char* fires,char* toadd);

char* MONS_IntToString(int num);

//Convert a string to Int
//---------------------------------------------------
//`text`:The Text to Convert
//---------------------------------------------------
//
int MONS_StringToInt(char* text);

//check if the `on` is in the text
//---------------------------------------------------
//`text` :The Text to check
//`on` :What to check
//---------------------------------------------------
MSBool MONS_FindInString(char* text,char on);

char* MONS_MergeString(char** Strings,uint64_t Length);

MSBool MONS_CheckIfEqualStringFromPos(char* Original,char* Find);

//Get a String Length
//---------------------------------------------------
//`String`:The String to the Length from
//---------------------------------------------------
//`If` the String is NULL it will return 0
uint64_t MONS_StringLength(char* String);


uint64_t MONS_StringCopy(char* CopyTo,char* From);

char* MONS_DupeString(char* String);
#endif
