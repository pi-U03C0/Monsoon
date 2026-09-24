#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MONS_BasicDrawStorage* MONS_BasicDrawComponentStorage = NULL;

void MONS_ZeroAllBasicDrawContexts()
{
  for (uint16_t i = 0 ; i < MONSOON_BASICDRAW_CONTEXT_LIMIT ; i++)
  {
    MONS_BasicDrawComponentStorage -> Contexts[i].ID = 0;
    if (MONS_BasicDrawComponentStorage -> Contexts[i].TargetResources)
    {
     for (uint16_t j = 0 ; j < MONS_BasicDrawComponentStorage -> Contexts[i].ResourceCount ; j++)
     {
       RemoveMemory(MONS_BasicDrawComponentStorage -> Contexts[i].TargetResources[j]);
     }
     RemoveMemory(MONS_BasicDrawComponentStorage -> Contexts[i].TargetResources);
    }
    MONS_BasicDrawComponentStorage -> Contexts[i].ResourceCount = 0;
  }
}

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
