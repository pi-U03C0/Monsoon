#ifndef MONSOON_UTILS_STRING_H
#define MONSOON_UTILS_STRING_H

#define GET_SPLIT_SIZE(text) ((unsigned long long)(text-1)[0])

#define REMOVE_SPLIT(texts)\
    do {\
        for (uint64_t i = 0 ; i < GET_SPLIT_SIZE(texts) ; i++)\
        { \
          RemoveMemory(texts[i]);\
        }\
    } while(0);

#include <Monsoon/Monsoon.h>

//Split a String with on
//---------------------------------------------------
//`text`:The Text to Split
//`on`:What to split on
//---------------------------------------------------
//`The` Return Split String array Length is one address before the address that was return
//`For` Example if the return address was 0x1000001 than the Length will be at 0x1000000
//`All` version of the function come with a macro called GET_SPLIT_SIZE to get the Length
MONS_API char** MONS_SplitString(char* text,char on);

//Find a sub string in a String and Replace it with it Replacement
//---------------------------------------------------
//`Original`:The String in
//`Find`:The Sub-String to Find
//`Replace`:The String to Replace with
//---------------------------------------------------
//Make Sure to Free it with RemoveMemory
MONS_API char* MONS_FindAndReplaceString(char* Original,char* Find,char* Replace);

//Compone two string
//---------------------------------------------------
//`First`:The Fisrt String
//`Second`:The Second String
//---------------------------------------------------
//Make Sure to Free it with RemoveMemory
MONS_API char* MONS_AddString(char* First,char* Second);

MONS_API char* MONS_IntToString(int num);

//Convert a string to Int
//---------------------------------------------------
//`text`:The Text to Convert
//---------------------------------------------------
MONS_API int MONS_StringToInt(char* text);

//check if the `on` is in the text
//---------------------------------------------------
//`text` :The Text to check
//`on` :What to check
//---------------------------------------------------
MONS_API MSBool MONS_FindInString(char* text,char on);

MONS_API char* MONS_MergeString(char** Strings,uint64_t Length);

MONS_API MSBool MONS_CheckIfEqualStringFromPos(char* Original,char* Find);

//Get a String Length
//---------------------------------------------------
//`String`:The String to the Length from
//---------------------------------------------------
//`If` the String is NULL it will return 0
MONS_API uint64_t MONS_StringLength(char* String);

MONS_API uint64_t MONS_StringCopy(char* CopyTo,char* From);

MONS_API char* MONS_DupeString(char* String);

#endif
