#ifndef MONSOON_H
#define MONSOON_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #define MONSOON_OS_WINDOWS 1
  #define MONSOON_PLATFORM_NT 1
#endif

#if defined(__linux__) || defined (__linux)
  #define MONSOON_OS_LINUX 1
  #define MONSOON_PLATFORM_POSIX 1
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
  #define MONSOON_OS_BSD 1
  #define MONSOON_PLATFORM_POSIX 1
#endif

#if defined(__ANDROID__)
  #define MONSOON_OS_ANDROID 1
  #define MONSOON_PLATFORM_POSIX 1
#endif

#define MONSOON_USE_MALLOC 1
#define MONSON_DEBUG 1

#ifndef MONSOON_FILE_INDEX_NAME
  #define MONSOON_FILE_INDEX_NAME "FileIndex.index"
#endif

#ifdef MONSOON_USE_MALLOC
  #define GetMemory malloc
  #define RemoveMemory free
#else
  #define GetMemory MONS_AllocMemory
  #define RemoveMemory MONS_DeAllocMemory
#endif

#include <Monsoon/MONS_Types.h>
extern MONS_Library* __Monsoon;

#include <Monsoon/MONS_Init.h>
#include <Monsoon/MONS_Window.h>
#include <Monsoon/MONS_Memory.h>
#include <Monsoon/MONS_Error.h>
#include <Monsoon/MONS_Process.h>
#include <Monsoon/MONS_Log.h>
#include <Monsoon/MONS_Console.h>
#include <Monsoon/MONS_FileSystem.h>
#include <Monsoon/MONS_Event.h>
#include <Monsoon/MONS_Proc.h>
#include <Monsoon/MONS_Time.h>
#include <Monsoon/MONS_Components.h>

#include <Monsoon/Platform/Platform.h>
#include <Monsoon/Structure/Structure.h>
#include <Monsoon/Utils/Utils.h>
#include <Monsoon/Graphic/Graphic.h>

#ifdef INCLUDE_STD
  #include <stdio.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
