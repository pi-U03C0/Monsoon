#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <stdio.h>

#ifdef MONSOON_PLATFORM_NT
int Win32_WGLAttributes[] = (int[]){
  WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
  WGL_CONTEXT_MINOR_VERSION_ARB, 6,
  WGL_CONTEXT_PROFILE_MASK_ARB,
  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
  0
};
#endif

MONS_OpenGLContext* MONS_CreateBasicOpenGLContext(MONS_Window* Window)
{
  LOG("Window = 0x%p",MONSOON_LOG_DEBUG,255,Window);
  MONS_OpenGLContext* Context = GetMemory(sizeof(MONS_OpenGLContext));
  if (!Context)
  {
    Error_Memory();
    return NULL;
  }

  #ifdef MONSOON_PLATFORM_NT
    if (!MONS_Win32_SetPixelFormat(Window -> RenderSurface))
    {
      goto err_frees;
    }
  #endif

  Context -> GLContext = glCreateContext(Window -> RenderSurface);
  if (!Context -> GLContext)goto err_frees;
  Context -> RenderSurface = Window -> RenderSurface;

  return Context;

err_frees:
  if (Context) RemoveMemory(Context);
  LOG("Error Create Context",MONSOON_LOG_ERROR,10);
  return NULL;
}

MONS_OpenGLContext* MONS_CreateOpenGLContext(MONS_Window* Window,int* GLAttributes)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,255,Window);
    return NULL;
  }

  LOG("Window = 0x%p",MONSOON_LOG_DEBUG,255,Window);
  MONS_OpenGLContext* Context = GetMemory(sizeof(MONS_OpenGLContext));
  if (!Context)
  {
    Error_Memory();
    return NULL;
  }
  #ifdef MONSOON_PLATFORM_NT
    if (!MONS_Win32_SetPixelFormat(Window -> RenderSurface))
    {
      goto err_frees;
    }
    if (!GLAttributes)
    {
    }
  #endif

  Context -> GLContext = glCreateContextAttribsARB(Window -> RenderSurface,NULL,GLAttributes);
  Context -> RenderSurface = Window -> RenderSurface;

  return Context;
err_frees:
  if (Context) RemoveMemory(Context);
  return NULL;
}

MSBool MONS_MakeCurrentOpenGLContext(MONS_OpenGLContext* Context)
{
  LOG("Context = 0x%p,Context -> GLContext = 0x%p,Context -> RenderSurface = 0x%p",MONSOON_LOG_DEBUG,255,Context,Context -> GLContext,Context -> RenderSurface);
  if (!Context)
  {
    LOG("Context was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  if (!Context -> GLContext)
  {
    LOG("The GLContext was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  if (!Context -> RenderSurface)
  {
    LOG("The Context RenderSurface was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  return glMakeCurrent(Context -> RenderSurface,Context -> GLContext);
}

MSBool MONS_RemoveCurrentOpenGLContect()
{
  return glMakeCurrent(NULL,NULL);
}

