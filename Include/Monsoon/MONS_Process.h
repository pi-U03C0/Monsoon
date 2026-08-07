#ifndef MONSOON_PROCESS_INFO_H
#define MONSOON_PROCESS_INFO_H

#include <Monsoon/MONS_Types.h>

//Get the Process Working Directory
char* MONS_GetCurrentWorkingDirectory();

uint32_t MONS_GetProcessId();

char* MONS_GetEnvironmentVariable(char* Name);

#endif
