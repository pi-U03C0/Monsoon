#ifndef MONSOON_INIT_H
#define MONSOON_INIT_H

#include <Monsoon/MONS_Types.h>

#ifndef MONSOON_ONEXIT_LEN
  #define MONSOON_ONEXIT_LEN 16
#endif

#define MONSOON_ONEXIT_UNUSED (void*)1

#define MONSOON_INIT_OPENGL 1
#define MakeInit_ComponentsOption(...) (uint16_t*)(uint16_t[]){__VA_ARGS__,0}

// Initialized The Monsoon Library
MSBool MONSInit(uint16_t* Components,uint8_t LogLevel);

// UnInitialized The Monsoon Library
MSBool MONSTerminate();

//Add a Function to a array with is run when MONSTerminate is called
MSBool MONS_AddOnExitFunction(ExitFunciton fn);

//Remove a Function from OnExit array
MSBool MONS_RemoveOnExitFunction(ExitFunciton fn);

//Initialized a Components of Monsoon or Mutitple
MSBool MONS_InitializComponents(uint16_t* Components);

//Convert a Component to String
char* MONS_ComponentToString(uint16_t Component);

//Get The Monsoon version
uint64_t MONS_GetVersion();

#endif
