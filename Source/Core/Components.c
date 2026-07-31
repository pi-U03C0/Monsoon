#include <Monsoon/Monsoon.h>

char* MONS_ComponentToString(uint16_t Component)
{
  switch (Component)
  {
    case MONSOON_INIT_OPENGL:return "OpenGL";
    default:return "?";
  }
}
