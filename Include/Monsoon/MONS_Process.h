#ifndef MONSOON_PROCESS_INFO_H
#define MONSOON_PROCESS_INFO_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Monsoon.h>

//Get the Process Working Directory
MONS_API char* MONS_GetCurrentWorkingDirectory();

MONS_API uint32_t MONS_GetProcessId();

MONS_API char* MONS_GetEnvironmentVariable(char* Name);

#endif
