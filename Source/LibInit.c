#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Monsoon/MONS_Log.h"
#include "Monsoon/Monsoon.h"

MONS_LIBRARY_InternalObject* __Monsoon = NULL;

MSBool MONSInit()
{
  __Monsoon = (MONS_LIBRARY_InternalObject *)malloc( sizeof(MONS_LIBRARY_InternalObject));

  if (!__Monsoon) return False;

  __Monsoon -> IsInitialized = True;

  __Monsoon -> OnExit = GetMemory(sizeof(void*)*MONSOON_ONEXIT_LEN);


  #if MONSOON_LOG_LEVEL >= MONSOON_LOG_INFO
    LOG("Initialized; Monsoon",MONSOON_LOG_INFO,1);
  #endif

  return True;
}

MSBool MONSTerminate()
{
  if (!__Monsoon) goto not_init;
  if (!__Monsoon -> IsInitialized) goto not_init;

//  for (int i = 0 ; __Monsoon -> OnExit[i]; i++)
//  {
//     __Monsoon -> OnExit[i]();
//  }

  RemoveMemory(__Monsoon);

  #if MONSOON_LOG_INFO >= MONSOON_LOG_INFO
    LOG("Terminate Monsoon",MONSOON_LOG_INFO,1);
  #endif

  return True;

  not_init:
  return False;
}
