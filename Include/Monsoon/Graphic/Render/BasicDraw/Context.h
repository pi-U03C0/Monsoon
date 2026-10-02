#ifndef MONSOON_GRAPHIC_RENDER_BASICDRAW_CONTEXT_H
#define MONSOON_GRAPHIC_RENDER_BASICDRAW_CONTEXT_H

#define MONSOON_BASICDRAW_CONTEXT_LIMIT 10

#include <Monsoon/Monsoon.h>

MONS_API MONS_BasicDrawContext* MONS_GetBasicDrawContext(uint16_t ContextID);
MONS_API MONS_BasicDrawContext* MONS_GetEmptyBasicDrawContext();
MONS_API void MONS_CheckBasicDrawContextCache(uint8_t ContextID);
MONS_API uint8_t MONS_CreateBasicDrawContext();
MONS_API uint8_t MONS_GetNextBasicDrawContextID();
MONS_API void MONS_ZeroAllBasicDrawContexts();
MONS_API MSBool MONS_RemoveBasicDrawContext(uint8_t ContextID);

#endif
