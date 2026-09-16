#ifndef MONSOON_GRAPHIC_API_OPENGL_GL_CONTEXT_H
#define MONSOON_GRAPHIC_API_OPENGL_GL_CONTEXT_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/Monsoon.h>

MONS_API MONS_OpenGLContext* MONS_CreateBasicOpenGLContext(MONS_Window* Window);

//-------------------------------------------------------------------------------------------
//`Set` the Current Thread OpenGL Context
//-Parameters--------------------------------------------------------------------------------
//`Context`:The OpenGL Context
//-Return------------------------------------------------------------------------------------
MONS_API MSBool MONS_MakeCurrentOpenGLContext(MONS_OpenGLContext* Context);

//-------------------------------------------------------------------------------------------
//`Remove` the Current OpenGL Context for the Current Thread
//-Return------------------------------------------------------------------------------------
//`True` if it was remove SuccseeFully,False if there was no Context
//-------------------------------------------------------------------------------------------
MONS_API MSBool MONS_RemoveCurrentOpenGLContect();

//-------------------------------------------------------------------------------------------
//`Create` a OpenGL Context for the Passin Window
//-Parameters--------------------------------------------------------------------------------
//`Window`:The Window to Create the Context for,It Must Be a Valid Window
//`GLAttributes`:Attributes to Use to Create the Context,This Can Be Null
//-Return------------------------------------------------------------------------------------
//`The` Newly Create OpenGL Context,if Context Createtion Faileds it will be Null
MONS_API MONS_OpenGLContext* MONS_CreateOpenGLContext(MONS_Window* Window,int* GLAttributes);

//-------------------------------------------------------------------------------------------
//`Create` a OpenGL Context for the Passin Window
//-Return------------------------------------------------------------------------------------
//`Return` The Major,Miner OpenGL Version
MONS_API MONS_OpenGLVersion MONS_GetOpenGLVersion();

MONS_API MSBool MONS_SetCurrentOpenGLPrograme(MONS_OpenGLContext* Context,uint32_t Programe);

#endif

