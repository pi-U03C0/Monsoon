#ifndef MONSOON_INIT_H
#define MONSOON_INIT_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Monsoon.h>

#ifndef MONSOON_ONEXIT_LEN
  #define MONSOON_ONEXIT_LEN 16
#endif

#define MONSOON_ONEXIT_UNUSED (void*)1
#define MONSOON_INIT_COMPONENT 1000

#define Component(x) MONSOON_INIT_COMPONENT,x
#define MakeInit_Flags(...) (uint16_t*)(uint16_t[]){__VA_ARGS__,0}

// Initialized The Monsoon Library
MONS_API MSBool MONSInit(uint16_t* Components,uint8_t LogLevel);

// UnInitialized The Monsoon Library
MONS_API MSBool MONSTerminate();

MONS_API MSBool MONS_AllocatMonsoon();

//Add a Function to a array with is run when MONSTerminate is called
MONS_API MSBool MONS_AddOnExitFunction(ExitFunciton fn);

//Remove a Function from OnExit array
MONS_API MSBool MONS_RemoveOnExitFunction(ExitFunciton fn);

//Get The Monsoon version
MONS_API uint64_t MONS_GetVersion();

#endif
