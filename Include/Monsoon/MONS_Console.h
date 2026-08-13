#ifndef MONSOON_CONSOLE_H
#define MONSOON_CONSOLE_H

#include "Monsoon/Monsoon.h"
#include <Monsoon/MONS_Types.h>

//Write To Stdout
//---------------------------------------------
//`Message`:The String to Write
//---------------------------------------------
MONS_API int MONS_WriteStdOutput(char* Message);

//Write To The StdErr
//---------------------------------------------
//`Message`:The String to Write
//---------------------------------------------
MONS_API int MONS_WriteStdError(char* Message);

//Write To The StdInput?
//---------------------------------------------
//`Message`:The String to Write
//---------------------------------------------
//`It` does not work or i think so i do not known why to use this function but it exists
MONS_API int MONS_WriteStdInput(char* Message);

//Check if StdInput is Connect to a Console or is a Pipe
MONS_API MSBool MONS_StdInputIsConsole();

#endif
