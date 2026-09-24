#ifndef MONSOON_GRAPHIC_RENDER_BASICDRAW_CONTEXT_H
#define MONSOON_GRAPHIC_RENDER_BASICDRAW_CONTEXT_H

#define MONSOON_BASICDRAW_CONTEXT_LIMIT 10

#include <Monsoon/Monsoon.h>

MONS_BasicDrawContext* MONS_GetBasicDrawContext(uint16_t ContextID);
MSBool MONS_CheckBasicDrawContextCache(uint16_t ContextID);

#endif
