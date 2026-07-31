#include "Monsoon/Monsoon.h"
#include <stdio.h>

MONS_Library* __Monsoon = NULL;

MSBool MONSInit(uint16_t* Components,uint8_t LogLevel)
{
  //check if Monsoon was Initialized
  if (!__Monsoon)
  {
    //allocate and Initializ __Monsoon
    __Monsoon = (MONS_Library *)GetMemory( sizeof(MONS_Library));
    if (!__Monsoon)//mem error
    {
      Error_Memory();
      return False;
    }
    __Monsoon -> IsInitialized = True;
    __Monsoon -> state.WindowCount = 0;

    //Initializ OnExit
    __Monsoon -> OnExit = GetMemory(sizeof(void*)*(MONSOON_ONEXIT_LEN+1));
    if (!__Monsoon -> OnExit)
    {
      Error_Memory();
      return False;
    }
    for (int i = 0 ; i < MONSOON_ONEXIT_LEN ; i++) __Monsoon -> OnExit[i] = MONSOON_ONEXIT_UNUSED;
  }

  //set log Level
  __Monsoon -> state.LogLevel = LogLevel;

  //check if ProcArray was Initialized
  if (!MONS_InitProcArray())
  {
    LOG("Unable to Initializ ProcArray",MONSOON_LOG_WARNING,10);
  }

  if (Components)//check if Components is NULL
  {
    //Initialized Components
    if (!MONS_InitializComponents(Components))
    {
      LOG("Unable to Initialized Components",MONSOON_LOG_CRITICAL,2);
      return False;
    }
    __Monsoon -> Components = (uint16_t*)MONS_DupeMemory((void*)Components, sizeof(uint16_t) * (MONS_ComponentsCount(Components)+1));
  }

  LOG("Initialized Monsoon",MONSOON_LOG_INFO,1);

  return True;
}

MSBool MONSTerminate()
{
  //check if Monsoon was Initialized
  if (!__Monsoon) goto not_init;
  if (!__Monsoon -> IsInitialized) goto not_init;

  LOG("Terminating Monsoon",MONSOON_LOG_INFO,2);

  //called the exit functions
  for (int i = 0 ; i < MONSOON_ONEXIT_LEN ; i++)
  {
     if (!__Monsoon -> OnExit[i])continue; //if it NUL
     if (__Monsoon -> OnExit[i] == MONSOON_ONEXIT_UNUSED)continue;
     __Monsoon -> OnExit[i]();
  }

  //free memory
  RemoveMemory(__Monsoon -> OnExit);
  RemoveMemory(__Monsoon);

  LOG("Terminated Monsoon",MONSOON_LOG_SUCCESS,1);

  return True;

  not_init: return False;
}

MSBool MONS_AddOnExitFunction(ExitFunciton fn)
{
  //check if a slot is free if yes add the function and return
  for (int i = 0 ; i < MONSOON_ONEXIT_LEN ; i++)
  {
    if (__Monsoon -> OnExit[i] != MONSOON_ONEXIT_UNUSED) continue;
    __Monsoon -> OnExit[i] = fn;
    return True;
  }

  return False;
}

MSBool MONS_RemoveOnExitFunction(ExitFunciton fn)
{
  //check if the onexit array have fn if yes than remove it
  for (int i = 0 ; i < MONSOON_ONEXIT_LEN ; i++)
  {
    if (!__Monsoon -> OnExit[i]) continue;
    if (__Monsoon -> OnExit[i] != MONSOON_ONEXIT_UNUSED) continue;
    if (__Monsoon -> OnExit[i] == fn)__Monsoon -> OnExit[i] = MONSOON_ONEXIT_UNUSED;
    return True;
  }
  return False;
}

MSBool MONS_InitializComponents(uint16_t* Components)
{
  for (uint16_t i = 0 ; Components[i] ; i++)
  {
    LOG("Components: %s",MONSOON_LOG_DEBUG,255,MONS_ComponentToString(Components[i]));
  }
  return True;
}

MSBool MONS_DeInitializComponents(int Components)
{
  return False;
}

MSBool MONS_InitProcArray()
{
  MONS_Procs = GetMemory(sizeof(MONS_Proc)*(MONSOON_PROC_LEN+1));
  if (!MONS_Procs)
  {
    Error_Memory();
    return False;
  }

  uint16_t i = 0;
  for (; i < MONSOON_PROC_LEN ; i++)
  {
    MONS_Procs[i].Type = MONS_ProcsDefine[i].Type;
    MONS_Procs[i].Proc = MONS_GetProcAddress(MONS_ProcsDefine[i].Proc);
    if (!MONS_Procs[i].Proc) LOG("Unable to set Proc for %d",MONSOON_LOG_WARNING,1,MONS_Procs[i].Type);
  }
  MONS_Procs[i].Type = 0;
  MONS_Procs[i].Proc = NULL;

  return True;
}

uint16_t MONS_ComponentsCount(uint16_t* Components)
{
  uint16_t i = 0;
  for (; Components[i] ; i++);
  return i;
}

uint64_t MONS_GetVersion()
{
  return MONSOON_VERSION;
}
