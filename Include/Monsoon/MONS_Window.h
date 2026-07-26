#ifndef MONSOON_WINDOW_H
#define MONSOON_WINDOW_H

#include <Monsoon/MONS_Types.h>

#define MONS_SHOW_WINDOW 1

// Create A Window
MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect);

//Show a Window
MSBool MONS_ShoWindow(MONS_Window* Window,char act);

//Close the Widnow
MSBool MONS_CloseWindow(MONS_Window* Window);

//Convert Act to OS show command
int MONS_ActToMode(char act);

//Poll Event from the window
MSBool MONS_WindowPollEvent(MONS_Window* Window);

MONS_Event* MONS_PopWindowEvent(MONS_Window* Window);
MSBool MONS_PushWindowEvent(MONS_Window* Window,MONS_Event* Event);

#endif
