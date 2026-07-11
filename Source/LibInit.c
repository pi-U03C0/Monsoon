#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Monsoon/MONS_Types.h"
#include "Monsoon/Monsoon.h"

MONS_LIBRARY_InternalObject* __Monsoon = NULL;

MSBool MONSInit()
{
  printf("djskjs\n");

  __Monsoon = (MONS_LIBRARY_InternalObject*)GetMemory(sizeof(MONS_LIBRARY_InternalObject));

  if (!__Monsoon) return False;

  __Monsoon -> IsInitialized = True;
  return True;
}

MSBool MONSTerminate()
{
  if (!__Monsoon) goto not_init;
  if (!__Monsoon -> IsInitialized) goto not_init;

  RemoveMemory(__Monsoon);

  return True;

  not_init:
  fprintf(stderr,"MONSTerminate: Monsoon is not Initialized");
  return False;
}
