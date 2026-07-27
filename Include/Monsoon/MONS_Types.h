#ifndef MONSOON_TYPES_H
#define MONSOON_TYPES_H

#include <stdint.h>

#include <Monsoon/SystemHeaders.h>

typedef char MSBool;

#ifdef _WIN32
typedef HANDLE OSFileHandle;
typedef HANDLE OSWindowHandle;
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

//OnExitFunction type
typedef void (*ExitFunciton)(void);

struct MONS_Rect
{
  short X;
  short Y;
  short Width;
  short Height;
}; typedef struct MONS_Rect MONS_Rect;

struct MONS_Queue
{
  //Read Pos
  uint16_t PopPos;
  //Write Pos
  uint16_t PushPos;
  uint16_t Capacity;
  uint64_t* Items;
};typedef struct MONS_Queue MONS_Queue;

struct MONSError {
  uint64_t Code;
  uint8_t  ErrorReason;
  uint8_t  ProjectPart;
  uint16_t Function;
  uint16_t SourceFile;
  uint16_t ErrorLine;
  char* Message;
}; typedef struct MONSError MONSError;

struct LibraryState {
  uint8_t WindowCount;
  uint8_t LogLevel;
  char extra[128];
}; typedef struct LibraryState LibraryState;

struct MONS_Library
{
  MSBool IsInitialized;
  LibraryState state;
  MONSError Error;
  void (**OnExit)(void);
  uint16_t* Components;
}; typedef struct MONS_Library MONS_Library;

struct MONS_Window
{
  OSWindowHandle OSHandle;
  MONS_Rect* WindowArea;
  char* Title;
  MONS_Queue* Events;
}; typedef struct MONS_Window MONS_Window;

struct MONS_File
{
  OSFileHandle OSHandle;
  char* FilePath;
  uint64_t FileSize;
}; typedef struct MONS_File MONS_File;

struct MONS_Event
{
  uint64_t Type;
  void* Prarms;
};typedef struct MONS_Event MONS_Event;

struct MONS_Proc
{
  uint16_t Type;
  void* Proc;
};typedef struct MONS_Proc MONS_Proc;

#endif
