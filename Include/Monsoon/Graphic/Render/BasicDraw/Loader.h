#ifndef MONSOON_GRAPHIC_RENDER_BASICDRAW_LOADER_H
#define MONSOON_GRAPHIC_RENDER_BASICDRAW_LOADER_H

#include <Monsoon/Monsoon.h>

MONS_API extern uint16_t MONS_BasicDrawComponent;

MONS_API extern MONS_BasicDrawStorage* MONS_BasicDrawComponentStorage;

MSBool MONS_InitComponentBasicDraw();

MSBool MONS_DeInitComponentBasicDraw();


MSBool MONS_InitBasicDrawStorage();

MSBool MONS_DeInitBasicDrawStorage();

#endif
