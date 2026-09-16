#include <Monsoon/Monsoon.h>
#include <stdio.h>

uint16_t MONS_BasicDrawComponent = 0;

MSBool MONS_InitComponentBasicDraw()
{
  if (!MONS_IsInitComponent(MONSOON_COMPONENT_OPENGL))
  {
    MONS_InitializComponent(MONSOON_COMPONENT_OPENGL);
  }
  LOG("Init BasicDraw",MONSOON_LOG_SUCCESS,0);
  return True;
}

MSBool MONS_DeInitComponentBasicDraw()
{
  MONS_De
  return True;
}
