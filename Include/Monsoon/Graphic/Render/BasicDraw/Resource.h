#ifndef MONSOON_GRAPHIC_API_RENDER_BASICDRAW_RESOURCE_H
#define MONSOON_GRAPHIC_API_RENDER_BASICDRAW_RESOURCE_H

#include <Monsoon/Monsoon.h>

enum MONS_ResourceType
{
  MONSOON_RESOURCE_TYPE_NULL,
  MONSOON_RESOURCE_TYPE_MATRIX,
  MONSOON_RESOURCE_TYPE_OPENGL_SHADER
};

MSBool MONS_LoadBasicDrawResourceShader(uint16_t ContextID,char* Shader);
MONS_BasicDrawResource* MONS_GetBasicDrawContextResource(uint16_t ContextID,uint16_t Type);

#endif
