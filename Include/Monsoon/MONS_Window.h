#ifndef MONSOON_WINDOW_H
#define MONSOON_WINDOW_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Monsoon.h>

#define MONS_SHOW_WINDOW 1

// Create A Window
MONS_API MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect);

//Show a Window
MONS_API MSBool MONS_ShoWindow(MONS_Window* Window,char act);

//Close the Widnow
MONS_API MSBool MONS_CloseWindow(MONS_Window* Window);

//Convert Act to OS show command
MONS_API int MONS_ActToMode(char act);

//Poll Event from the window
MONS_API MSBool MONS_PollWindowEvent(MONS_Window* Window);

//Pop the Last Event
//-------------------------------------------
//`Window`:The Window To pop the Event from
//-------------------------------------------
//`Make` sure to Free the Pointer with RemoveMemory or FreeEvent after processing it
//`Example`:
//- Event = MONS_PopWindowEvent(Window);
//- if (Event)
//- {
//-  `if (Event -> Type == MONSOON_EVENT_QUIT)
//-  `{
//-  `  ...
//-  `}
//-  `FreeEvent(Event);
//- }
MONS_API MONS_Event* MONS_PopWindowEvent(MONS_Window* Window);

//Push a Event to the window Event
MONS_API MSBool MONS_PushWindowEvent(MONS_Window* Window,MONS_Event* Event);

MONS_API OSHandle MONS_GetWindowDrawSurface(MONS_Window* Window);

MONS_API MSBool MONS_SwapWindowDrawBuffers(MONS_Window* Window);

#endif
