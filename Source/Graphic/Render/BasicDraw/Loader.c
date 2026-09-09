#include <Monsoon/Monsoon.h>
#include <stdio.h>

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
  return True;
}
