#include "Monsoon/MONS_Types.h"
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
        if (!(MONS_Components -> Components[i].Init()))
        {
          LOG("Unable to Initializ Component \"%s\"",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_GET,MONS_ComponentToString(MONS_Components -> Components[i].Type));
          return False;
        }
        LOG("Initialized Component \"%s\"",MONSOON_LOG_SUCCESS,0,MONS_ComponentToString(MONS_Components -> Components[i].Type));
    }
  }
  return True;
}

MSBool MONS_AppendComponent(MSBool Type,void* Init,void* DeInit)
{
  for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
  {
    if ((MONS_Components -> Components[i].Type == 0) || (MONS_Components -> Components[i].Type == Type))
    {
      MONS_Components -> Components[i].Type = Type;
      MONS_Components -> Components[i].Init = Init;
      return True;
    }
  }
  return False;
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
  for (; Components[i] ; i++);
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
   MONS_AppendComponent(MONSOON_COMPONENT_OPENGL, MONS_InitComponentOpenGL,MONS_DeInitComponentOpenGL);
   return True;
}

MSBool MONS_InitBasicDrawArrayPart()
{
   MONS_AppendComponent(MONSOON_COMPONENT_BASICDRAW, MONS_InitComponentBasicDraw,MONS_DeInitComponentBasicDraw);
   return True;
}
