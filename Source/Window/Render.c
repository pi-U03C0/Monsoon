#include "Monsoon/Platform/Win32/Window.h"
#include <Monsoon/Monsoon.h>
#include <Monsoon/Platform/Platform.h>

OSHandle MONS_GetWindowDrawSurface(MONS_Window* Window)
{
  #ifdef _WIN32
     MONS_Win32_GetWindowDrawSurface(Window -> OSHandle);
  #endif
}
