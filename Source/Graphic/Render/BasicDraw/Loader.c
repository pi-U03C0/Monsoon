#include "Monsoon/MONS_Types.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

uint8_t MONS_BasicDrawComponent = 0;
MONS_BasicDrawStorage* MONS_BasicDrawComponentStorage = NULL;

MSBool MONS_InitComponentBasicDraw(MONS_ComponentList* ComponentList)
{
  if (!MONS_IsInitComponent(ComponentList,MONSOON_COMPONENT_OPENGL))
  {
    MONS_InitializComponent(ComponentList,MONSOON_COMPONENT_OPENGL);
  }
  MONS_InitBasicDrawStorage(ComponentList);
  LOG("Init BasicDraw",MONSOON_LOG_SUCCESS,0);
  return True;
}

MSBool MONS_DeInitComponentBasicDraw(MONS_ComponentList* ComponentList)
{
  MONS_DeInitBasicDrawStorage();
  return True;
}

MSBool MONS_InitBasicDrawStorage(MONS_ComponentList* ComponentList)
{
  MONS_Component* BasicDraw = &(ComponentList -> Components[MONS_BasicDrawComponent]);
  BasicDraw -> Storage = GetMemory(sizeof(MONS_BasicDrawStorage));
  MONS_BasicDrawComponentStorage = (ComponentList -> Components[MONS_BasicDrawComponent].Storage);
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
