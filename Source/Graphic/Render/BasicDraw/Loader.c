#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

uint8_t MONS_BasicDrawComponent = 0;
MONS_BasicDrawStorage* MONS_BasicDrawComponentStorage = NULL;

MSBool MONS_InitComponentBasicDraw()
{
  if (!MONS_IsInitComponent(MONSOON_COMPONENT_OPENGL))
  {
    MONS_InitializComponent(MONSOON_COMPONENT_OPENGL);
  }
  MONS_InitBasicDrawStorage();
  LOG("Init BasicDraw",MONSOON_LOG_SUCCESS,0);
  return True;
}

MSBool MONS_DeInitComponentBasicDraw()
{
  MONS_DeInitBasicDrawStorage();
  return True;
}
