#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MSBool MONS_InitBasicDrawStorage()
{
  MONS_Component* BasicDraw = &(MONS_Components -> Components[MONS_BasicDrawComponent]);
  BasicDraw -> Storage = GetMemory(sizeof(MONS_BasicDrawStorage));
  MONS_BasicDrawComponentStorage = (MONS_Components -> Components[MONS_BasicDrawComponent].Storage);
  MONS_BasicDrawComponentStorage -> Contexts = GetMemory(sizeof(MONS_BasicDrawContext)*MONSOON_BASICDRAW_CONTEXT_LIMIT);

  MONS_ZeroAllBasicDrawContexts();

  return True;
}

MSBool MONS_DeInitBasicDrawStorage()
{
  MONS_Component* BasicDraw = &(MONS_Components -> Components[MONS_BasicDrawComponent]);
  if (BasicDraw -> Storage)RemoveMemory(BasicDraw -> Storage);

  return True;
}
