#ifndef MONSOON_EVENT_H
#define MONSOON_EVENT_H

#include "Monsoon/MONS_Proc.h"

#define FreeEvent(x) \
    do { \
        if ((x) -> Prarms) RemoveMemory((x)->Prarms); \
        RemoveMemory(x); \
    } while (0)

enum MONSOON_Event
{
  MONSOON_EVENT_QUIT,
  MONSOON_EVENT_WINDOW_CLOSE,
  MONSOON_EVENT_WINDOW_OPEN,
};

#endif
