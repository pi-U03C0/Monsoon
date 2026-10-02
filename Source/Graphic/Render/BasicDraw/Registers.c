#include "Monsoon/MONS_Error.h"
#include <Monsoon/Monsoon.h>

MSBool MONS_RegisterBasicDrawWindow(uint8_t ContextID,MONS_Window* Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_WAS_NULL,MONSOON_LOG_ERROR);
    return False;
  }

  MONS_BasicDrawStorage* Storage = (MONS_Components -> Components[MONS_BasicDrawComponent].Storage);
  MONS_BasicDrawContext* Context = MONS_GetBasicDrawContext(ContextID);
  if (!Context)
  {
    LOG("Invaild ContextID %d",MONSOON_LOG_ERROR,MONSOON_LOG_INVALID,ContextID);
    return False;
  }

  if (Context -> Window)
  {
    MONS_SetErrorCode(Make_Code(MONSOON_LOG_ALRIGHT_THERE));
    return False;
  }

  return True;
}

MSBool MONS_UnRegisterBasicDrawWindow(uint8_t ContextID)
{
  MONS_BasicDrawStorage* Storage = (MONS_Components -> Components[MONS_BasicDrawComponent].Storage);
  MONS_BasicDrawContext* Context = MONS_GetBasicDrawContext(ContextID);
  if (!Context)
  {
    LOG("Invaild ContextID %d",MONSOON_LOG_ERROR,MONSOON_LOG_INVALID,ContextID);
    return False;
  }

  Context -> Window = NULL;

  return True;
}
