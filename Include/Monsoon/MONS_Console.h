#ifndef MONSOON_CONSOLE_H
#define MONSOON_CONSOLE_H

#include <Monsoon/MONS_Types.h>

int MONS_WriteStdOutput(char* Message);

int MONS_WriteStdError(char* Message);

int MONS_WriteStdInput(char* Message);

MSBool MONS_StdInputIsConsole();

#endif
