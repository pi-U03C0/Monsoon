#ifndef MONSOON_GRAPHIC_RENDER_BASICDRAW_REGISTERS_H
#define MONSOON_GRAPHIC_RENDER_BASICDRAW_REGISTERS_H

#define MONSOON_BASICDRAW_REGISTER_WINDOW_LIMIT 5

#include <Monsoon/Monsoon.h>

MONS_API MSBool MONS_RegisterBasicDrawWindow(uint8_t ContextID,MONS_Window* Window)

MONS_API MSBool MONS_UnRegisterBasicDrawWindow(uint8_t ContextID,MONS_Window* Window);

#endif
