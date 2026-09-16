#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MSBool MONS_InitBasicDrawStorage()
{
  MONS_Component* BasicDraw = &(MONS_Components -> Components[MONS_BasicDrawComponent]);
  BasicDraw -> Storage = GetMemory(sizeof(MONS_BasicDrawStorage));

  return True;
}

MSBool MONS_DeInitBasicDrawStorage()
{
  MONS_Component* BasicDraw = &(MONS_Components -> Components[MONS_BasicDrawComponent]);
  if (BasicDraw -> Storage)RemoveMemory(BasicDraw -> Storage);

  return True;
}
