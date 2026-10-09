#ifndef MONSOON_GRAPHIC_RENDER_BASICDRAW_LOADER_H
#define MONSOON_GRAPHIC_RENDER_BASICDRAW_LOADER_H

#include <Monsoon/Monsoon.h>

MONS_API extern uint8_t MONS_BasicDrawComponent;

MONS_API extern MONS_BasicDrawStorage* MONS_BasicDrawComponentStorage;

MONS_API extern MSBool MONS_InitComponentBasicDraw(MONS_ComponentList* ComponentList);
MONS_API extern MSBool MONS_DeInitComponentBasicDraw(MONS_ComponentList* ComponentList);
MONS_API extern MSBool MONS_InitBasicDrawStorage();
MONS_API extern MSBool MONS_DeInitBasicDrawStorage();


#endif
