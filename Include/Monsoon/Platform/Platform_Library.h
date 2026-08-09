#ifndef MONSOON_PLATFORM_LIBRARY_H
#define MONSOON_PLATFORM_LIBRARY_H

#define MONSOON_LIBRARY_UNUSED 1

#include <Monsoon/MONS_Types.h>

//Load a Library File(*.dll,*.so)
//-----------------------------------------------------------
//`DLLPath`:Path to Dynamic Library to Load
//`LoadFlags`:How to load the Library File
//-----------------------------------------------------------
//`LoadFlags` Current does nothing but it Planed for the futuer
MONS_DynamicLibrary* MONS_LoadLibrary(char* DLLPath,uint16_t LoadFlags);

//Free The Library
//-----------------------------------------------------------
//`Library`:Pointer to the Library Object
//-----------------------------------------------------------
MSBool MONS_FreeLibrary(MONS_DynamicLibrary* Library);

//Get a Function Address
//-----------------------------------------------------------
//`ProcName`:The Name of the Function To get the Address
//`Library`:Pointer to the Library Object
//-----------------------------------------------------------
//`If` Library is NULL it search the Currnet Exe and the Monsoon DLL
void* MONS_GetProcAddress(const char* ProcName,MONS_DynamicLibrary* Library);

//Append a Library Object to the gloabal List to be auto close At Term
//-----------------------------------------------------------
//`Library`:The Library to append
//-----------------------------------------------------------
//`Thes` Library will be auto Free On Exit
MSBool MONS_AppendToGlobalLibrary(MONS_DynamicLibrary* Library);

//Close All Library loaded by Monsoon
void MONS_CloseAllLibrary();

//Check if More Library Can Be Loaded
MSBool MONS_IsAtLimitLibrary();

#endif
