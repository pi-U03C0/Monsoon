#define INCLUDE_STD
#include <Monsoon/Monsoon.h>

MONS_Library* __Monsoon = NULL;
MONS_ComponentList* MONS_Components = NULL;

MSBool MONSInit(uint16_t* Flags,uint8_t LogLevel)
{
  //check if Monsoon was Initialized
  if (!__Monsoon)
  {
    if (!MONS_AllocatMonsoon())return False;
  }
  __Monsoon -> state.LogLevel = LogLevel;

  LOG("Initializing Monsoon",MONSOON_LOG_INFO,MONSOON_LOG_INIT);

  if (!MONS_Components)
  {
    MONS_Components = MONS_InitComponentArray(MONSOON_COMPONENT_LENGHT);
  }

  MONS_ExecuteFlags(Flags);

  MONS_AddOnExitFunction(MONS_CloseAllFile);
  MONS_AddOnExitFunction(MONS_CloseAllLibrary);

  LOG("Initialized Monsoon",MONSOON_LOG_INFO,MONSOON_LOG_INIT);

  return True;
}

MSBool MONSTerminate()
{
  //check if Monsoon was Initialized
  if (!__Monsoon) goto not_init;
  if (!__Monsoon -> IsInitialized) goto not_init;

  LOG("Terminating Monsoon",MONSOON_LOG_INFO,MONSOON_LOG_TERMINATE);

  //called the exit functions
  for (int i = 0 ; i < MONSOON_ONEXIT_LEN ; i++)
  {
     if (!__Monsoon -> OnExit[i])continue; //if it NUL
     if (__Monsoon -> OnExit[i] == MONSOON_ONEXIT_UNUSED)continue;
     __Monsoon -> OnExit[i]();
  }

  MONS_CloseAllLibrary();
  MONS_CloseAllFile();
  MONS_RemoveComponentList(MONS_Components);

  //free memory
  if (__Monsoon -> Flags)RemoveMemory(__Monsoon -> Flags);
  RemoveMemory(__Monsoon -> OnExit);
  RemoveMemory(__Monsoon -> LoadedLibrary);
  RemoveMemory(__Monsoon -> OpenFiles);
  RemoveMemory(__Monsoon);


  LOG("Terminated Monsoon",MONSOON_LOG_SUCCESS,1);

  return True;

  not_init: return False;
}

MSBool MONS_AllocatMonsoon()
{
  //allocate and Initializ __Monsoon
  __Monsoon = (MONS_Library *)GetMemory( sizeof(MONS_Library));
  if (!__Monsoon)
  {
    Error_Memory();
    return False;
  }

  //set Init values
  __Monsoon -> IsInitialized = True;
  __Monsoon -> state.WindowCount = 0;

  //Initializ OnExit
  LOG("Initializing OnExit",MONSOON_LOG_HIGHT_DEBUG,255);
  __Monsoon -> OnExit = GetMemory(sizeof(void*)*(MONSOON_ONEXIT_LEN+1));
  if (!__Monsoon -> OnExit)
  {
    Error_Memory();
    return False;
  } for (int i = 0 ; i < MONSOON_ONEXIT_LEN ; i++) __Monsoon -> OnExit[i] = MONSOON_ONEXIT_UNUSED;
  __Monsoon -> OnExit[MONSOON_ONEXIT_LEN] = NULL;

  LOG("Initializing LoadedLibrary",MONSOON_LOG_HIGHT_DEBUG,255);
  //Init the list of loaded Library
  __Monsoon -> LoadedLibrary = GetMemory(sizeof(MONS_DynamicLibrary*) * MONSOON_LIBRARY_LIMIT);
  if (!__Monsoon -> LoadedLibrary)
  {
    Error_Memory();
    return False;
  } for (uint16_t i = 0 ; i < MONSOON_LIBRARY_LIMIT ; i++) __Monsoon -> LoadedLibrary[i] = (void*)MONSOON_LIBRARY_UNUSED;

  LOG("Initializing OpenFiles",MONSOON_LOG_HIGHT_DEBUG,255);
  //Init the list of loaded files
  __Monsoon -> OpenFiles = GetMemory(sizeof(MONS_File*) * MONSOON_FILEOPEN_LIMIT);
  if (!__Monsoon -> OpenFiles)
  {
    Error_Memory();
    return False;
  } for (uint16_t i = 0 ; i < MONSOON_FILEOPEN_LIMIT ; i++) __Monsoon -> OpenFiles[i] = (void*)MONSOON_FILE_UNUSED;
  __Monsoon -> state.FileSearchPath = MONS_GetCurrentWorkingDirectory();

  return True;
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

void MONS_ExecuteFlags(uint16_t* Flags)
{
  MSBool CheckComponent = False;
  for (uint16_t i = 0 ; Flags[i] != MONSOON_FLAG_END ; i++)
  {
     if (Flags[i] == MONSOON_INIT_COMPONENT)
     {
       CheckComponent = True;
       continue;
     }

     if (CheckComponent)
     {
        MONS_InitializComponent(MONS_Components,Flags[i]);
        continue;
     }
  }
}

uint64_t MONS_GetVersion()
{
  return MONSOON_VERSION;
}
