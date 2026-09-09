#ifndef MONSOON_PLATFORM_H
#define MONSOON_PLATFORM_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Platform/Memory.h>
#include <Monsoon/Platform/FileSystem.h>
#include <Monsoon/Platform/Library.h>
#include <Monsoon/Platform/Time.h>
#include <Monsoon/Platform/Console.h>
#include <Monsoon/Platform/Process.h>
#include <Monsoon/Platform/KeyBoard.h>

#include <stddef.h>

#ifdef _WIN32
  #include <Monsoon/Platform/Win32/Win32.h>
#endif

#endif
