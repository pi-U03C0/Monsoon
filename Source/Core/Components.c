#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MONS_ComponentList* MONS_Components = NULL;

MONS_InitComponent MONS_InitComponentsArraryPart[] = {
  MONS_InitOpenGLArrayPart,
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
    return False;
  }

  for (uint16_t i = 0 ; i < MONSOON_COMPONENT_LENGHT ; i++)
  {
    MONS_Components -> Components[i].Type = 0;
    MONS_Components -> Components[i].Init = NULL;
  }
  MONS_Components -> Length = MONSOON_COMPONENT_LENGHT;

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
  if (MONS_Components -> Components)
  {
    RemoveMemory(MONS_Components -> Components);
  }

  if (MONS_Components)
  {
    RemoveMemory(MONS_Components);
  }
}

MSBool MONS_AppendComponent(MSBool Type,void* Init)
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

MSBool MONS_InitOpenGLArrayPart()
{
   MONS_AppendComponent(MONSOON_COMPONENT_OPENGL, MONS_InitComponentOpenGL);
   return True;
}

MSBool MONS_SetComponentInit(uint16_t Type)
{
   for (uint16_t i = 0 ; i < MONS_Components -> Length ; i++)
   {
     if (MONS_Components -> Components[i].Type == Type)
     {
        MONS_Components -> Components[i].IsInitialized = True;
        return True;
     }
   }
  return False;
}

char* MONS_ComponentToString(uint16_t Component)
{
  switch (Component)
  {
    case MONSOON_INIT_OPENGL||MONSOON_COMPONENT_OPENGL:return "OpenGL";
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

