#ifndef MONSOON_WINDOW_H
#define MONSOON_WINDOW_H

#include <Monsoon/MONS_Types.h>

#define MONS_SHOW_WINDOW 1

// Create A Window
MONS_Window* MONS_CreateWindow(char* Title,MONS_Rect* rect,void* WinProc);

//Show a Window
MSBool MONS_ShoWindow(MONS_Window* Window,char act);

//Close the Widnow
MSBool MONS_CloseWindow(MONS_Window* Window);

int MONS_ActToMode(char act);

#endif
