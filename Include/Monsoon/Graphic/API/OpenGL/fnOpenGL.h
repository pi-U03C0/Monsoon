#ifndef MONSOON_GRAPHIC_API_OPENGL_FUNCTION_H
#define MONSOON_GRAPHIC_API_OPENGL_FUNCTION_H

#include "Monsoon/Graphic/API/OpenGL/GL/glcorearb.h"
#include "Monsoon/Graphic/API/OpenGL/OpenGL.h"
#include <Monsoon/Monsoon.h>
#include <excpt.h>

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
MONS_API extern PFNGLCREATESHADERPROC MONS_glCreateShader;
MONS_API extern PFNGLSHADERSOURCEPROC MONS_glShaderSource;
MONS_API extern PFNGLCOMPILESHADERPROC MONS_glCompileShader;
MONS_API extern PFNGLGETSHADERIVPROC MONS_glGetShaderiv;
MONS_API extern PFNGLGETSHADERINFOLOGPROC MONS_glGetShaderInfoLog;
MONS_API extern PFNGLCREATEPROGRAMPROC MONS_glCreateProgram;
MONS_API extern PFNGLATTACHSHADERPROC MONS_glAttachShader;
MONS_API extern PFNGLGETPROGRAMIVPROC MONS_glGetProgramiv;
MONS_API extern PFNGLGETPROGRAMINFOLOGPROC MONS_glGetProgramInfoLog;
MONS_API extern PFNGLLINKPROGRAMPROC MONS_glLinkProgram;
MONS_API extern PFNGLGENBUFFERSPROC MONS_glGenBuffers;
MONS_API extern PFNGLBINDBUFFERPROC MONS_glBindBuffer;
MONS_API extern PFNGLGENVERTEXARRAYSPROC MONS_glGenVertexArrays;
MONS_API extern PFNGLBINDVERTEXARRAYPROC MONS_glBindVertexArray;
MONS_API extern PFNGLVERTEXATTRIBPOINTERPROC MONS_glVertexAttribPointer;
MONS_API extern PFNGLENABLEVERTEXATTRIBARRAYPROC MONS_glEnableVertexAttribArray;
MONS_API extern PFNGLBUFFERDATAPROC MONS_glBufferData;
MONS_API extern PFNGLUSEPROGRAMPROC MONS_glUseProgram;
MONS_API extern PFNGLDRAWELEMENTSPROC MONS_glDrawElements;
MONS_API extern PFNGLPOLYGONMODEPROC MONS_glPolygonMode;
MONS_API extern PFNGLGETUNIFORMLOCATIONPROC MONS_glGetUniformLocation;
MONS_API extern PFNGLUNIFORM1FPROC MONS_glUniform1f;
MONS_API extern PFNGLDELETESHADERPROC MONS_glDeleteShader;
MONS_API extern PFNGLDELETEPROGRAMPROC MONS_glDeleteProgram;
MONS_API extern PFNGLGETPROGRAMINTERFACEIVPROC MONS_glGetProgramInterfaceiv;
MONS_API extern PFNGLGETPROGRAMRESOURCEIVPROC MONS_glGetProgramResourceiv;
MONS_API extern PFNGLGETPROGRAMRESOURCENAMEPROC MONS_glGetProgramResourceName;
MONS_API extern PFNGLGETACTIVEUNIFORMPROC MONS_glGetActiveUniform;
MONS_API extern PFNGLUNIFORM3FPROC MONS_glUniform3f;
MONS_API extern PFNGLGETINTEGERVPROC MONS_glGetIntegerv;
MONS_API extern PFNGLUNIFORMMATRIX4FVPROC MONS_glUniformMatrix4fv;
MONS_API extern PFNGLUNIFORM2FPROC MONS_glUniform2f;

#define wglCreateContext MONS_wglCreateContext
#define wglMakeCurrent MONS_wglMakeCurrent
#define wglDeleteContext MONS_wglDeleteContext
#define wglGetProcAddress MONS_wglGetProcAddress
#define wglCreateContextAttribsARB MONS_wglCreateContextAttribsARB
#define glGetString MONS_glGetString
#define glClear MONS_glClear
#define glClearColor MONS_glClearColor
#define glCreateShader MONS_glCreateShader
#define glShaderSource MONS_glShaderSource
#define glCompileShader MONS_glCompileShader
#define glGetShaderiv MONS_glGetShaderiv
#define glGetShaderInfoLog MONS_glGetShaderInfoLog
#define glGenBuffers MONS_glGenBuffers
#define glGetProgramInfoLog MONS_glGetProgramInfoLog
#define glCreateProgram MONS_glCreateProgram
#define glAttachShader MONS_glAttachShader
#define glLinkProgram MONS_glLinkProgram
#define glGetProgramiv MONS_glGetProgramiv
#define glBindBuffer MONS_glBindBuffer
#define glGenVertexArrays MONS_glGenVertexArrays
#define glBindVertexArray MONS_glBindVertexArray
#define glVertexAttribPointer MONS_glVertexAttribPointer
#define glEnableVertexAttribArray MONS_glEnableVertexAttribArray
#define glBufferData  MONS_glBufferData
#define glUseProgram MONS_glUseProgram
#define glDrawElements MONS_glDrawElements
#define glPolygonMode MONS_glPolygonMode
#define glGetUniformLocation MONS_glGetUniformLocation
#define glUniform1f MONS_glUniform1f
#define glDeleteShader MONS_glDeleteShader
#define glDeleteProgram MONS_glDeleteProgram
#define glGetProgramInterfaceiv MONS_glGetProgramInterfaceiv
#define glGetProgramResourceiv MONS_glGetProgramResourceiv
#define glGetProgramResourceName MONS_glGetProgramResourceName
#define glGetActiveUniform MONS_glGetActiveUniform
#define glUniform3f MONS_glUniform3f
#define glGetIntegerv MONS_glGetIntegerv
#define glUniformMatrix4fv MONS_glUniformMatrix4fv
#define glUniform2f MONS_glUniform2f

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
#define sglCreateShader            "glCreateShader"
#define sglShaderSource            "glShaderSource"
#define sglGetShaderiv             "glGetShaderiv"
#define sglGetShaderInfoLog        "glGetShaderInfoLog"
#define sglCreateProgram           "glCreateProgram"
#define sglAttachShader            "glAttachShader"
#define sglLinkProgram             "glLinkProgram"
#define sglGetProgramiv            "glGetProgramiv"
#define sglGetProgramInfoLog       "glGetProgramInfoLog"
#define sglGenBuffers              "glGenBuffers"
#define sglBindBuffer              "glBindBuffer"
#define sglGenVertexArrays         "glGenVertexArrays"
#define sglBindVertexArray         "glBindVertexArray"
#define sglVertexAttribPointer     "glVertexAttribPointer"
#define sglEnableVertexAttribArray "glEnableVertexAttribArray"
#define sglBufferData              "glBufferData"
#define sglUseProgram              "glUseProgram"
#define sglDrawElements            "glDrawElements"
#define sglCompileShader           "glCompileShader"
#define sglPolygonMode             "glPolygonMode"
#define sglGetUniformLocation      "glGetUniformLocation"
#define sglUniform1f               "glUniform1f"
#define sglDeleteShader            "glDeleteShader"
#define sglDeleteProgram           "glDeleteProgram"
#define sglGetProgramInterfaceiv   "glGetProgramInterfaceiv"
#define sglGetProgramResourceiv    "glGetProgramResourceiv"
#define sglGetProgramResourceName  "glGetProgramResourceName"
#define sglGetActiveUniform        "glGetActiveUniform"
#define sglUniform3f               "glUniform3f"
#define sglGetIntegerv             "glGetIntegerv"
#define sglUniformMatrix4fv        "glUniformMatrix4fv"
#define sglUniform2f               "glUniform2f"

#endif
