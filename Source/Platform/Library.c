#include <Monsoon/Monsoon.h>
#include <string.h>

MONS_DynamicLibrary* MONS_LoadLibrary(char* DLLPath,uint16_t LoadFlags)
{
   if (!(__Monsoon -> state.LoadedLibraryCount > MONSOON_LIBRARY_LIMIT))
   {
     LOG("Too Many Library Loaded",MONSOON_LOG_CRITICAL,MONSOON_LOG_WAS_FULL);
     return NULL;
   }

   MONS_DynamicLibrary* Library = GetMemory(sizeof(MONS_DynamicLibrary));

   #ifdef MONSOON_PLATFORM_NT
      Library -> OSHandle = MONS_Win32_LoadLibrary(DLLPath);
   #endif

   if (!Library -> OSHandle)
   {
     LOG("Unable to load Library \"%s\"",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
   }

   Library -> DLLPath = strdup(DLLPath);
   Library -> LoadFlags = LoadFlags;

  return Library;
}

MSBool MONS_FreeLibrary(MONS_DynamicLibrary* Library)
{
  #ifdef MONSOON_PLATFORM_NT
     MSBool Success = MONS_Win32_FreeLibrary(Library -> OSHandle);
  #endif

  if (Success)
  {
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

}
