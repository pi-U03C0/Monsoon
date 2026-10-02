#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MSBool (*MONS_BasicDrawAPIContextResourcesLoaders[])(uint8_t) = {
  0,
  MONS_GL_BasicDrawLoadContextResources
};

uint32_t MONS_BasicDrawRectangleResourcesIndices[] = {
    0, 1, 3,
    1, 2, 3
};

float MONS_BasicDrawRectangleResourcesVertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

MSBool MONS_LoadBasicDrawReactangleResources(uint8_t ContextID)
{
  if (MONS_BasicDrawComponentStorage -> API != MONSOON_GRAPHIC_API_NULL)
  {
    return False;
  }

  MONS_BasicDrawAPIContextResourcesLoaders[MONS_BasicDrawComponentStorage -> API](ContextID);
  return True;
}

MSBool MONS_LoadBasicDrawContextResources(uint8_t ContextID)
{

  MSBool Success = MONS_BasicDrawAPIContextResourcesLoaders[MONS_BasicDrawComponentStorage -> API](ContextID);
  if (!Success)
  {
    LOG("Cannot load Resource for Context %d",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
    return False;
  }
  return True;
}

MSBool MONS_GL_BasicDrawLoadContextResources(uint8_t ContextID)
{
  return True;
}
