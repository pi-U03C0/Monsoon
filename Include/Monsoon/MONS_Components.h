#ifndef MONSOON_COMPONENTS_H
#define MONSOON_COMPONENTS_H

#include <Monsoon/MONS_Types.h>

#define MONSOON_COMPONENT_LENGHT 10

enum ComponentType
{
   MONSOON_COMPONENT_NULL,
   MONSOON_COMPONENT_OPENGL,
   MONSOON_COMPONENT_BASICDRAW
};

extern MONS_ComponentList* MONS_Components;

//Init the Component Array
MSBool MONS_InitComponentArray(uint16_t Length);

MSBool MONS_InitializComponent(uint16_t Component);

//Check if a Component Exists
MSBool MONS_IsComponent(uint16_t Component);

MSBool MONS_IsInitComponent(uint16_t Component);


//Convert a Component to String
char* MONS_ComponentToString(uint16_t Component);

//Count the Amout of the Components
uint16_t MONS_ComponentsCount(uint16_t* Components);

MSBool MONS_InitOpenGLArrayPart();
MSBool MONS_InitBasicDrawArrayPart();

MSBool MONS_SetComponentInit(uint16_t Type,MSBool bool);

MONS_Component* MONS_RegisterComponent(uint16_t Type);

#endif
