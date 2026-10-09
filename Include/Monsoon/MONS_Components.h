#ifndef MONSOON_COMPONENTS_H
#define MONSOON_COMPONENTS_H

#include "Monsoon/MONS_Types.h"
#include <Monsoon/Monsoon.h>

#define MONSOON_COMPONENT_LENGHT 10
#define MONSOON_COMPONENT_UNUSED (void*)100

enum ComponentType
{
   MONSOON_COMPONENT_NULL,
   MONSOON_COMPONENT_OPENGL,
   MONSOON_COMPONENT_BASICDRAW,
};

MONS_API extern MONS_ComponentList* MONS_Components;

//Init the Component Array
MONS_API MONS_ComponentList* MONS_InitComponentArray(uint16_t Length);
MONS_API MSBool MONS_RemoveComponentList(MONS_ComponentList* ComponentList);

MONS_API MSBool MONS_InitializComponent(MONS_ComponentList* ComponentList,uint16_t Component);

//Check if a Component Exists
MONS_API MSBool MONS_IsComponent(MONS_ComponentList* ComponentList,uint16_t Component);

MONS_API MSBool MONS_IsInitComponent(MONS_ComponentList* ComponentList,uint16_t Component);

//Convert a Component to String
MONS_API char* MONS_ComponentToString(MONS_ComponentList* ComponentList,uint16_t Component);

//Count the Amout of the Components
MONS_API uint16_t MONS_ComponentsCount(uint16_t* Components);

MONS_API MSBool MONS_InitOpenGLArrayPart(MONS_ComponentList* ComponentList);
MONS_API MSBool MONS_InitBasicDrawArrayPart(MONS_ComponentList* ComponentList);

MONS_API MSBool MONS_SetComponentInit(MONS_ComponentList* ComponentList,uint16_t Type,MSBool bool);

MONS_API uint16_t MONS_RegisterComponent(MONS_ComponentList* ComponentList,uint16_t Type);


MONS_API MSBool MONS_DeInitComponent(MONS_ComponentList* ComponentList,uint16_t ID);

//Initialized Component of Monsoon or Mutitple Components
MONS_API MSBool MONS_InitializComponents(MONS_ComponentList* ComponentList,uint16_t* Components);

#endif
