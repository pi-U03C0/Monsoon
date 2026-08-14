#include <Monsoon/Monsoon.h>
#include <Monsoon/Platform/Platform.h>
#include <wingdi.h>

OSHandle MONS_GetWindowDrawSurface(MONS_Window* Window)
{
  #ifdef _WIN32
     return MONS_Win32_GetWindowDrawSurface(Window -> OSHandle);
  #endif
}

MSBool MONS_SwapWindowDrawBuffers(MONS_Window* Window)
{
  #ifdef MONSOON_PLATFORM_NT
     return SwapBuffers(Window -> RenderSurface);
  #endif
}

