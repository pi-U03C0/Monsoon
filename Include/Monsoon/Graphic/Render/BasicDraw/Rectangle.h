#ifndef MONSOON_GRAPHIC_RENDER_BASICDRAW_RECTANGLE_H
#define MONSOON_GRAPHIC_RENDER_BASICDRAW_RECTANGLE_H

#include <Monsoon/Monsoon.h>

MONS_API MSBool MONS_BasicDrawRectangle(uint16_t ContextID,MONS_Rect Rect,MONS_Colour Colour);
MONS_API MSBool MONS_GL_BasicDrawRectangle(MONS_BasicDrawContext* Context,MONS_Rect Rect,MONS_Colour Colour);
MONS_API MSBool MONS_GL_LoadBasicDrawReactangleResources(MONS_BasicDrawContext* Context);

#endif
