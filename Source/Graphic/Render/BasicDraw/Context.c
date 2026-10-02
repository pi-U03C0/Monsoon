#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

uint8_t MONS_CreateBasicDrawContext()
{
  MONS_BasicDrawContext* Context = MONS_GetEmptyBasicDrawContext();
  if (!Context)
  {
    LOG("No Available BasicDraw Context",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_FULL);
    return 0;
  }

  if (MONS_BasicDrawComponentStorage -> ContextCount >= MONSOON_BASICDRAW_CONTEXT_LIMIT)
  {
    MONS_SetErrorCode(Make_Code(MONSOON_LOG_WAS_FULL));
    return 0;
  }

  Context -> ID = MONS_GetNextBasicDrawContextID();
  Context -> ResourceCount = 0;
  Context -> WindowResourceLoaded = False;
  Context -> Window = NULL;
  return Context -> ID;
}

uint8_t MONS_GetNextBasicDrawContextID()
{
  if (MONS_BasicDrawComponentStorage -> ContextCount == 0)
  {
    return 1;
  }

  MSBool Found = False;
  uint8_t CheckID = 0;
  while (!Found && (CheckID < 255))
  {
    CheckID++;
    for (uint8_t i = 0 ; i < MONS_BasicDrawComponentStorage -> ContextCount ; i++)
    {
      if (MONS_BasicDrawComponentStorage -> Contexts[i].ID == CheckID)
      {
        Found = False;
        break;
      }
      Found = True;
    }
  }
  if (!Found)
  {
    return 0;
  }
  return CheckID;
}

MONS_BasicDrawContext* MONS_GetBasicDrawContext(uint16_t ContextID)
{
  MONS_BasicDrawStorage* Storage = MONS_Components -> Components[MONS_BasicDrawComponent].Storage;
  for (uint8_t i = 0 ; i < Storage -> ContextCount ; i++)
  {
    if (Storage -> Contexts[i].ID == ContextID)
      return &(Storage -> Contexts[i]);
  }
  return NULL;
}

void MONS_CheckBasicDrawContextCache(uint8_t ContextID)
{
  if (!(MONS_BasicDrawComponentStorage -> LastUsedContext))
  {
    MONS_BasicDrawComponentStorage -> LastUsedContext = MONS_GetBasicDrawContext(ContextID);
  }

  if (MONS_BasicDrawComponentStorage -> LastUsedContext -> ID == ContextID)
  {
    return;
  }
  else
  {
    MONS_BasicDrawComponentStorage -> LastUsedContext = MONS_GetBasicDrawContext(ContextID);
  }
}

MONS_BasicDrawContext* MONS_GetEmptyBasicDrawContext()
{
  MONS_BasicDrawStorage* Storage = MONS_Components -> Components[MONS_BasicDrawComponent].Storage;
  for (uint8_t i = 0 ; i < Storage -> ContextCount ; i++)
  {
    if (Storage -> Contexts[i].ID == 0)
    {
      return &(Storage -> Contexts[i]);
    }
  }
  return NULL;
}

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
