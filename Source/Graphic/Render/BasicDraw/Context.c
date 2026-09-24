#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

uint8_t MONS_CreateBasicDrawContext()
{
  
}

MONS_BasicDrawContext* MONS_GetBasicDrawContext(uint16_t ContextID)
{
  MONS_BasicDrawStorage* Storage = MONS_Components -> Components[MONS_BasicDrawComponent].Storage;
  for (uint16_t i = 0 ; i < Storage -> ContextCount ; i++)
  {
    if (Storage -> Contexts[i].ID == ContextID)
      return &(Storage -> Contexts[i]);
  }
  return NULL;
}

MSBool MONS_CheckBasicDrawContextCache()
{
  
}
