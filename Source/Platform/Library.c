#include <Monsoon/Monsoon.h>

MONS_DynamicLibrary* MONS_LoadLibrary(char* DLLPath,uint16_t LoadFlags)
{
   LOG("Loading Library %s with LoadFlags %d",MONSOON_LOG_DEBUG,255,DLLPath,LoadFlags);

   if ((!MONS_IsAtLimitLibrary()) || !(__Monsoon -> state.LoadedLibraryCount > MONSOON_LIBRARY_LIMIT))
   {
     LOG(
      "Can`t Load More than %d dynamic Library",
      MONSOON_LOG_CRITICAL,
      MONSOON_LOG_WAS_FULL,
      MONSOON_LIBRARY_LIMIT
     );

     MONS_SetErrorCode(Make_Code(MONSOON_LOG_WAS_FULL));
     return NULL;
   }

   MONS_DynamicLibrary* Library = GetMemory(sizeof(MONS_DynamicLibrary));
   if (!Library)
   {
     Error_Memory();
   }

   #ifdef MONSOON_PLATFORM_NT
      Library -> OSHandle = MONS_Win32_LoadLibrary(DLLPath);
   #endif

   if (!Library -> OSHandle)
   {
     LOG("Unable to load Library \"%s\"",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
   }

   Library -> DLLPath = MONS_DupeString(DLLPath);
   Library -> LoadFlags = LoadFlags;

   MONS_AppendToGlobalLibrary(Library);

  return Library;
}

MSBool MONS_FreeLibrary(MONS_DynamicLibrary* Library)
{
  #ifdef MONSOON_PLATFORM_NT
     MSBool Success = MONS_Win32_FreeLibrary(Library -> OSHandle);
  #endif

  if (Success)
  {
    RemoveMemory(Library -> DLLPath);
    RemoveMemory(Library);
  }
  return Success;
}

void* MONS_GetProcAddress(const char* ProcName,MONS_DynamicLibrary* Library)
{
  #ifdef MONSOON_PLATFORM_NT
    if (Library) return MONS_Win32_GetProcAddress(ProcName,Library -> OSHandle);
    else return MONS_Win32_GetProcAddress(ProcName,NULL);
  #endif

  #ifdef MONSOON_PLATFORM_POSIX
    if (Library)return MONS_Posix_GetProcAddress(ProcName,Library -> OSHandle)
    else return MONS_Posix_GetProcAddress(ProcName,NULL)
  #endif
}

MSBool MONS_AppendToGlobalLibrary(MONS_DynamicLibrary* Library)
{
  for (uint64_t i = 0 ; i < MONSOON_LIBRARY_LIMIT ; i++)
  {
    if (__Monsoon -> LoadedLibrary[i] == (void*)MONSOON_LIBRARY_UNUSED)
    {
      continue;
    }

    __Monsoon -> LoadedLibrary[i] = Library;
    return True;
  }
  return False;
}

MSBool MONS_RemoveFromGlobalLibrary(MONS_DynamicLibrary* Library)
{
  for (uint64_t i = 0 ; i < MONSOON_LIBRARY_LIMIT ; i++)
  {
    if (__Monsoon -> LoadedLibrary[i] == (void*)MONSOON_LIBRARY_UNUSED)
    {
      continue;
    }

    if (__Monsoon -> LoadedLibrary[i] == Library)
    {
      __Monsoon -> LoadedLibrary[i] = (void*)MONSOON_LIBRARY_UNUSED;
      return True;
    }
  }
  return False;
}

void MONS_CloseAllLibrary()
{
  for (uint64_t i = 0 ; i < MONSOON_LIBRARY_LIMIT ; i++)
  {
    if (__Monsoon -> LoadedLibrary[i] == (void*)MONSOON_LIBRARY_UNUSED)continue;
    if ((!__Monsoon -> LoadedLibrary[i] -> DLLPath) || (!__Monsoon -> LoadedLibrary[i] -> OSHandle))continue;

    MONS_FreeLibrary(__Monsoon -> LoadedLibrary[i]);
  }
}

MSBool MONS_IsAtLimitLibrary()
{
  for (uint64_t i = 0 ; i < MONSOON_LIBRARY_LIMIT ; i++)
  {
    if (__Monsoon -> LoadedLibrary[i] == (void*)MONSOON_LIBRARY_UNUSED)
    {
      return True;
    }
  }
  return False;
}
