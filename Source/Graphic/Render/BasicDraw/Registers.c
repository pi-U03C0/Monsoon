#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MSBool MONS_RegisterBasicDrawWindow(MONS_Window* Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_WAS_NULL,MONSOON_LOG_ERROR);
    return False;
  }
  MONS_BasicDrawStorage* Storage = (MONS_Components -> Components[MONS_BasicDrawComponent].Storage);

  if (Storage -> RegistersWindowsCount <= MONSOON_BASICDRAW_REGISTER_WINDOW_LIMIT)
  {
    LOG("Cannot Registers More than %d Window for BasicDraw",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
    return False;
  }

  for (uint8_t i = 0 ; i < Storage -> MONSOON_BASICDRAW_CONTEXT_LIMIT ; i++)
  {
     
  }

  return True;
}
