#include "Monsoon/MONS_Components.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <stdint.h>

MONS_ComponentList* MONS_Components = NULL;

MONS_InitComponent MONS_InitComponentsArraryPart[] = {
  MONS_InitOpenGLArrayPart,
  MONS_InitBasicDrawArrayPart,
  NULL
};

MSBool MONS_InitComponentArray(uint16_t Length)
{
  LOG("Initializing Component Array",MONSOON_LOG_DEBUG,255);
  if (!Length)return False;

  MONS_Components = GetMemory(sizeof(MONS_ComponentList));
  if (!MONS_Components)
  {
    Error_Memory();
    return False;
  }

  MONS_Components -> Components = GetMemory(sizeof(MONS_Component) * Length);
  if (!MONS_Components -> Components)
  {
    Error_Memory();
    RemoveMemory(MONS_Components);
    return False;
  }

  for (uint16_t i = 0 ; i < Length ; i++)
  {
    MONS_Components -> Components[i].Type = 0;
    MONS_Components -> Components[i].IsInitialized = False;
    MONS_Components -> Components[i].Init = NULL;
    MONS_Components -> Components[i].DeInit = NULL;
  }

  MONS_Components -> Length = Length;

  for (uint16_t i = 0 ; MONS_InitComponentsArraryPart[i] ; i++)
  {
    if (!MONS_InitComponentsArraryPart[i]())
    {
      return False;
    }
  }

  LOG("Initialized ComponentArray",MONSOON_LOG_INFO,MONSOON_LOG_INIT);

  return True;
}

void MONS_DeInitComponentArray()
{
  for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
  {
    if (MONS_Components[i].Components[i].IsInitialized)
    {
      MONS_Components[i].Components[i].DeInit();
    }
  }

  if (MONS_Components -> Components)
  {
    RemoveMemory(MONS_Components -> Components);
  }

  if (MONS_Components)
  {
    RemoveMemory(MONS_Components);
  }
}

MSBool MONS_InitializComponent(uint16_t Component)
{
  //go thoure the Register Components and running the init
  for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
  {
    if (MONS_Components -> Components[i].Type == Component)
    {
      LOG("Initializing Component \"%s\"",MONSOON_LOG_DEBUG,255,MONS_ComponentToString(Component));
      if (!(MONS_Components -> Components[i].Init()))
      {
        LOG("Unable to Initializ Component \"%s\"",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO,MONS_ComponentToString(MONS_Components -> Components[i].Type));
        return False;
      }
      LOG("Initialized Component \"%s\"",MONSOON_LOG_SUCCESS,0,MONS_ComponentToString(MONS_Components -> Components[i].Type));
      return True;
    }
  }
  return False;
}

MONS_Component* MONS_RegisterComponent(uint16_t Type)
{
  for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
  {
    if ((MONS_Components -> Components[i].Type == MONSOON_COMPONENT_NULL) || (MONS_Components -> Components[i].Type == Type))
    {
      MONS_Components -> Components[i].Type = Type;
      return &(MONS_Components -> Components[i]);
    }
  }
  return NULL;
}

MSBool MONS_SetComponentInit(uint16_t Type,MSBool bool)
{
   for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
   {
     if (MONS_Components -> Components[i].Type == Type)
     {
        MONS_Components -> Components[i].IsInitialized = bool;
        return True;
     }
   }
  return False;
}

char* MONS_ComponentToString(uint16_t Component)
{
  switch (Component)
  {
    case MONSOON_COMPONENT_OPENGL:return "OpenGL";
    case MONSOON_COMPONENT_BASICDRAW:return "BasicDraw";
    default:return "?";
  }
}

MSBool MONS_IsComponent(uint16_t Component)
{
  for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
  {
    if (MONS_Components -> Components[i].Type == Component)
    {
      return True;
    }
  }
  return False;
}

uint16_t MONS_ComponentsCount(uint16_t* Components)
{
  uint16_t i = 0;
  while (Components[i]) i++;
  return i;
}

MSBool MONS_IsInitComponent(uint16_t Component)
{
  for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
  {
    if (MONS_Components -> Components[i].Type == Component)
    {
      return MONS_Components -> Components[i].IsInitialized;
    }
  }
  return 2;
}

MSBool MONS_InitOpenGLArrayPart()
{
   MONS_Component* OpenGL = MONS_RegisterComponent(MONSOON_COMPONENT_OPENGL);
   if (!OpenGL)
   {
     LOG("Unable to Register OpenGL as a Component for Monsoon",MONSOON_LOG_CRITICAL,MONSOON_LOG_UNABLE_DO);
     return False;
   }

   OpenGL -> Init = MONS_InitComponentOpenGL;
   OpenGL -> DeInit = MONS_DeInitComponentOpenGL;
   return True;
}

MSBool MONS_InitBasicDrawArrayPart()
{
   MONS_Component* BasicDraw = MONS_RegisterComponent(MONSOON_COMPONENT_BASICDRAW);
   if (!BasicDraw)
   {
     LOG("Unable to Register BasicDraw as a Component for Monsoon",MONSOON_LOG_CRITICAL,MONSOON_LOG_UNABLE_DO);
     return False;
   }

   BasicDraw -> Init = MONS_InitComponentBasicDraw;
   BasicDraw -> DeInit = MONS_DeInitComponentBasicDraw;

   return True;
}
