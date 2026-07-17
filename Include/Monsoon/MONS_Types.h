#ifndef MONSOON_TYPES_H
#define MONSOON_TYPES_H

#include <stdint.h>

#include <Monsoon/SystemHeaders.h>

typedef char MSBool;

#ifdef _WIN32
typedef HANDLE OSFileHandle;
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

#if defined (__unix__)
  typedef int OSFileHandle
#endif

#ifndef True
  #define True 1
#endif
#ifndef False
  #define False 0
#endif

struct MONS_Rect
{
  short X;
  short Y;
  short Width;
  short Height;
}; typedef struct MONS_Rect MONS_Rect;

struct LibraryState {
  unsigned char WindowCount;
  unsigned char LogLevel;
  char extra[128];
}; typedef struct LibraryState LibraryState;

struct MONSError {
  uint64_t Code;
  uint8_t  ErrorReason;
  uint8_t  ProjectPart;
  uint16_t Function;
  uint16_t SourceFile;
  uint16_t ErrorLine;
  char* Message;
}; typedef struct MONSError MONSError;

struct MONS_LIBRARY_InternalObject
{
  MSBool IsInitialized;
  LibraryState state;
  MONSError Error;
  void (**OnExit)(void);
}; typedef struct MONS_LIBRARY_InternalObject MONS_LIBRARY_InternalObject;

struct MONS_Window
{
  void* OSHandle;
  MONS_Rect* WindowArea;
}; typedef struct MONS_Window MONS_Window;

struct MONS_File
{
  OSFileHandle OSHandle;
  char* FilePath;
  uint64_t FileSize;
}; typedef struct MONS_File MONS_File;

#endif
