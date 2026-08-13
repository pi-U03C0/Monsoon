#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MONS_OpenGLContext* MONS_CreateBasicOpenGLContext(MONS_Window* Window)
{
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

  LOG("glCreateContext = 0x%p",MONSOON_LOG_DEBUG,255,glCreateContext);
  Context -> GLContext = glCreateContext(Window -> RenderSurface);
  if (!Context -> GLContext)goto err_frees;
  Context -> RenderSurface = Window -> RenderSurface;

  return Context;

err_frees:
  if (Context) RemoveMemory(Context);
  return NULL;
}

MONS_OpenGLContext* MONS_CreateOpenGLContext(MONS_Window* Window,int* GLAttributes)
{
  MONS_OpenGLContext* Context = GetMemory(sizeof(MONS_OpenGLContext));
  if (!Context)
  {
    Error_Memory();
    return NULL;
  }

  Context -> GLContext = MONS_wglCreateContextAttribsARB(Window -> RenderSurface,NULL,GLAttributes);
  Context -> RenderSurface = Window -> RenderSurface;

  return Context;
}

MSBool MONS_MakeCurrentOpenGLContext(MONS_OpenGLContext* Context)
{
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
