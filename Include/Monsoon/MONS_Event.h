#ifndef MONSOON_EVENT_H
#define MONSOON_EVENT_H

#include <Monsoon/Monsoon.h>

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
  MONSOON_EVENT_WINDOW_CHANGE_SIZE,
  MONSOON_EVENT_WINDOW_MOVE,
  MONSOON_EVENT_WINDOW_FOCUS,
  MONSOON_EVENT_WINDOW_LOST_FOCUS,
  MONSOON_EVENT_KEY_DOWN,
  MONSOON_EVENT_KEY_UP,
  MONSOON_EVENT_TEXT
};

#endif
