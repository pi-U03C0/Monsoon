#ifndef MONSOON_GRAPHIC_API_OPENGL
#define MONSOON_GRAPHIC_API_OPENGL

#include <Monsoon/Monsoon.h>

#include <Monsoon/Graphic/API/OpenGL/GL/glcorearb.h>
#include <Monsoon/Graphic/API/OpenGL/GL/glext.h>
#include <Monsoon/Graphic/API/OpenGL/GL/gl.h>

#ifdef MONSOON_PLATFORM_NT
  #include <Monsoon/Graphic/API/OpenGL/GL/wglext.h>
  #include <Monsoon/Graphic/API/OpenGL/GL/wgl.h>
#endif

#include <Monsoon/Graphic/API/OpenGL/fnOpenGL.h>
#include <Monsoon/Graphic/API/OpenGL/Loader.h>
#include <Monsoon/Graphic/API/OpenGL/Context.h>
#include <Monsoon/Graphic/API/OpenGL/Shader.h>
#include <Monsoon/Graphic/API/OpenGL/Vertext.h>
#include <Monsoon/Graphic/API/OpenGL/Uniform.h>

#endif
