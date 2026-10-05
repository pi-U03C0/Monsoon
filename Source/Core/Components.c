#include "Monsoon/MONS_Types.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MONS_InitComponent MONS_InitComponentsArraryPart[] = {
  MONS_InitOpenGLArrayPart,
  MONS_InitBasicDrawArrayPart,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  MONSOON_COMPONENT_UNUSED,
  NULL
};

MONS_ComponentList* MONS_InitComponentArray(uint16_t Length)
{
  LOG("Initializing Component Array",MONSOON_LOG_DEBUG,255);
  if (!Length)
  {
    LOG("ComponentArray Length was 0",MONSOON_LOG_CRITICAL,MONSOON_LOG_WAS_NULL);
    return False;
  }

  MONS_ComponentList* ComponentList = GetMemory(sizeof(MONS_ComponentList));
  if (!ComponentList)
  {
    Error_Memory();
    return False;
  }

  ComponentList -> Components = GetMemory(sizeof(MONS_Component) * Length);
  if (!ComponentList -> Components)
  {
    Error_Memory();
    RemoveMemory(ComponentList);
    return False;
  }

  for (uint16_t i = 0 ; i < Length ; i++)
  {
    ComponentList -> Components[i].ID = 0;
    ComponentList -> Components[i].IsInitialized = False;
    ComponentList -> Components[i].Init = NULL;
    ComponentList -> Components[i].DeInit = NULL;
  }

  ComponentList -> Length = Length;

  for (uint16_t i = 0 ; MONS_InitComponentsArraryPart[i] ; i++)
  {
    if (MONS_InitComponentsArraryPart[i] == MONSOON_COMPONENT_UNUSED)
    {
      continue;
    }

    if (!MONS_InitComponentsArraryPart[i](ComponentList))
    {
      return False;
    }
  }

  LOG("Initialized ComponentArray",MONSOON_LOG_INFO,MONSOON_LOG_INIT);

  return ComponentList;
}

MSBool MONS_InitializComponent(MONS_ComponentList* ComponentList,uint16_t Component)
{
  //go thoure the Register Components and running the init
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if (ComponentList -> Components[i].ID == Component)
    {
      LOG("Initializing Component \"%s\"",MONSOON_LOG_DEBUG,255,MONS_ComponentToString(ComponentList,Component));
      if (!(ComponentList -> Components[i].Init(ComponentList)))
      {
        LOG("Unable to Initializ Component \"%s\"",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO,MONS_ComponentToString(ComponentList,ComponentList -> Components[i].ID));
        return False;
      }
      LOG("Initialized Component \"%s\"",MONSOON_LOG_SUCCESS,0,MONS_ComponentToString(ComponentList,ComponentList -> Components[i].ID));
      return True;
    }
  }
  return False;
}

uint16_t MONS_RegisterComponent(MONS_ComponentList* ComponentList,uint16_t ID)
{
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if ((ComponentList -> Components[i].ID == MONSOON_COMPONENT_NULL) || (ComponentList -> Components[i].ID == ID))
    {
      ComponentList -> Components[i].ID = ID;
      return i;
    }
  }
  return NULL;
}

MSBool MONS_SetComponentInit(MONS_ComponentList* ComponentList,uint16_t Type,MSBool bool)
{
   for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
   {
     if (ComponentList -> Components[i].ID == Type)
     {
        ComponentList -> Components[i].IsInitialized = bool;
        return True;
     }
   }
  return False;
}

char* MONS_ComponentToString(MONS_ComponentList* ComponentList,uint16_t ID)
{
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if (ComponentList -> Components[i].ID == ID)
    {
      if (!(ComponentList -> Components[i].Name))
      {
        return "?";
      }
      else
      {
        return ComponentList -> Components[i].Name;
      }
    }
  }
}

MSBool MONS_IsComponent(MONS_ComponentList* ComponentList,uint16_t Component)
{
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if (ComponentList -> Components[i].ID == Component)
    {
      return True;
    }
  }
  return False;
}

uint16_t ComponentListCount(uint16_t* Components)
{
  uint16_t i = 0;
  while (Components[i]) i++;
  return i;
}

MSBool MONS_IsInitComponent(MONS_ComponentList* ComponentList,uint16_t Component)
{
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if (ComponentList -> Components[i].ID == Component)
    {
      return ComponentList -> Components[i].IsInitialized;
    }
  }
  return 2;
}

MSBool MONS_DeInitComponent(MONS_ComponentList* ComponentList,uint16_t ID)
{
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if (ComponentList -> Components[i].ID == ID)
    {
      if (ComponentList -> Components[i].IsInitialized)
      {
        ComponentList -> Components[i].DeInit(ComponentList);
        return True;
      }
      else
      {
        return False;
      }
    }
  }
  return False;
}

MSBool MONS_DeInitAllComponets(MONS_ComponentList* ComponentList)
{
  for (uint16_t i = 0 ; i < ComponentList -> Length ; i++)
  {
    if ((ComponentList -> Components[i].IsInitialized) || (ComponentList -> Components[i].ID != 0))
    {
      ComponentList -> Components[i].DeInit(ComponentList);
    }
  }
  return False;
}

MSBool MONS_InitializComponents(MONS_ComponentList* ComponentList,uint16_t* Components)
{
  LOG("Initializing Components",MONSOON_LOG_DEBUG,255);
  for (uint16_t i = 0 ; Components[i] ; i++)
  {
    //check if is a Component
    if (MONS_IsComponent(ComponentList,Components[i]))
    {
      MONS_InitializComponent(ComponentList,Components[i]);
    }
    else
    {
      LOG("UnKnown Component %d",MONSOON_LOG_ERROR,MONSOON_LOG_UNKNOWN,Components[i]);
    }
  }
  LOG("Initialized All Components",MONSOON_LOG_INFO,MONSOON_LOG_INFO);
  return True;
}

MSBool MONS_RemoveComponentList(MONS_ComponentList* ComponentList)
{
  if (!ComponentList)
  {
    LOG("ComponentList was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  

}

MSBool MONS_InitOpenGLArrayPart(MONS_ComponentList* ComponentList)
{
   uint16_t OpenGL = MONS_RegisterComponent(ComponentList,MONSOON_COMPONENT_OPENGL);
   if (OpenGL == MONSOON_LOG_WAS_FULL)
   {
     LOG("Unable to Register OpenGL as a Component for Monsoon",MONSOON_LOG_CRITICAL,MONSOON_LOG_UNABLE_DO);
     return False;
   }

   ComponentList -> Components[OpenGL].Init = MONS_InitComponentOpenGL;
   ComponentList -> Components[OpenGL].DeInit = MONS_DeInitComponentOpenGL;
   ComponentList -> Components[OpenGL].Name = "OpenGL";

   MONS_OpenGLComponent = OpenGL;
   return True;
}

MSBool MONS_InitBasicDrawArrayPart(MONS_ComponentList* ComponentList)
{
  uint16_t BasicDraw = MONS_RegisterComponent(ComponentList,MONSOON_COMPONENT_BASICDRAW);
  if (!BasicDraw)
  {
    LOG("Unable to Register BasicDraw as a Component for Monsoon",MONSOON_LOG_CRITICAL,MONSOON_LOG_UNABLE_DO);
    return False;
  }

  ComponentList -> Components[BasicDraw].Init = MONS_InitComponentBasicDraw;
  ComponentList -> Components[BasicDraw].DeInit = MONS_DeInitComponentBasicDraw;
  ComponentList -> Components[BasicDraw].Name = "BasicDraw";
  MONS_BasicDrawComponent = BasicDraw;

  return True;
}

