#ifndef MONSOON_H
#define MONSOON_H

#ifdef __cplusplus
extern "C" {
#endif

#define MONSOON_USE_MALLOC
#define MONSON_DEBUG

#ifdef MONSOON_USE_MALLOC
#define GetMemory malloc
#define RemoveMemory free
#else
#define GetMemory MONS_AllocMemory
#define RemoveMemory MONS_DeAllocMemory
#endif

#include <Monsoon/MONS_Types.h>
extern MONS_LIBRARY_InternalObject* __Monsoon;

#include <Monsoon/MONS_Init.h>
#include <Monsoon/MONS_Window.h>
#include <Monsoon/MONS_Memory.h>
#include <Monsoon/MONS_Error.h>
#include <Monsoon/MONS_ProcessInfo.h>
#include <Monsoon/MONS_Log.h>
#include <Monsoon/MONS_Console.h>
#include <Monsoon/MONS_FileSystem.h>

#include <Monsoon/Platform/Platform.h>

#ifdef INCLUDE_STD
#endif

#ifdef __cplusplus
}
#endif

#endif
