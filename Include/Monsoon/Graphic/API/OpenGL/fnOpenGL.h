#ifndef MONSOON_GRAPHIC_API_OPENGL_FUNCTION_H
#define MONSOON_GRAPHIC_API_OPENGL_FUNCTION_H

#include "Monsoon/Graphic/API/OpenGL/OpenGL.h"
#include <Monsoon/Monsoon.h>

MONS_API extern PFNWGLCREATECONTEXTPROC  MONS_wglCreateContext;
MONS_API extern PFNWGLMAKECURRENTPROC    MONS_wglMakeCurrent;
MONS_API extern PFNWGLDELETECONTEXTPROC  MONS_wglDeleteContext;
MONS_API extern PFNWGLGETPROCADDRESSPROC MONS_wglGetProcAddress;
MONS_API extern PFNWGLCREATECONTEXTATTRIBSARBPROC MONS_wglCreateContextAttribsARB;
MONS_API extern PFNWGLCHOOSEPIXELFORMATARBPROC MONS_wglChoosePixelFormatARB;
MONS_API extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
MONS_API extern PFNGLGETSTRINGPROC MONS_glGetString;
MONS_API extern PFNGLCLEARPROC MONS_glClear;
MONS_API extern PFNGLCLEARCOLORPROC MONS_glClearColor;

#define wglCreateContext MONS_wglCreateContext
#define wglMakeCurrent MONS_wglMakeCurrent
#define wglDeleteContext MONS_wglDeleteContext
#define wglGetProcAddress MONS_wglGetProcAddress
#define wglCreateContextAttribsARB MONS_wglCreateContextAttribsARB
#define glGetString MONS_glGetString
#define glClear MONS_glClear
#define glClearColor MONS_glClearColor

#ifdef MONSOON_PLATFORM_NT
#define glCreateContext wglCreateContext
#define glMakeCurrent wglMakeCurrent
#define glDeleteContext wglDeleteContext
#define glGetProcAddress wglGetProcAddress
#define glCreateContextAttribsARB wglCreateContextAttribsARB
#endif

#ifdef MONSOON_PLATFORM_NT
#define sglCreateContext           "wglCreateContext"
#define sglMakeCurrent             "wglMakeCurrent"
#define sglDeleteContext           "wglDeleteContext"
#define sglGetProcAddress          "wglGetProcAddress"
#define sglCreateContextAttribsARB "wglCreateContextAttribsARB"
#endif

#define sglClear                   "glClear"
#define sglClearColor              "glClearColor"
#define sglGetString               "glGetString"

#endif
