#ifndef MONSOON_GRAPHIC_API_RENDER_BASICDRAW_RESOURCE_H
#define MONSOON_GRAPHIC_API_RENDER_BASICDRAW_RESOURCE_H

#include <Monsoon/Monsoon.h>

//Index into the Context Resources,0 is allway NULL
enum MONS_BasicdrawResourcesIndex
{
  MONSOON_BASICDRAW_RESOURCES_INDEX_NULL,
  MONSOON_BASICDRAW_RESOURCES_INDEX_GLOABLE,
  MONSOON_BASICDRAW_RESOURCES_INDEX_RECTANGLE,
};

MONS_API MSBool MONS_GL_BasicDrawLoadContextResources(uint8_t ContextID);
MONS_API MSBool MONS_GL_UnLoadBasicDrawContextResources(uint8_t ContextID);
MONS_API MSBool MONS_LoadBasicDrawContextResources(uint8_t ContextID);
MONS_API MSBool MONS_UnLoadBasicDrawContextResources(uint8_t ContextID);

#endif
