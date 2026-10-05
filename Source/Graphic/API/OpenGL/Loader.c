#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/API/OpenGL/OpenGL.h>
#include <Monsoon/SystemHeaders.h>

MONS_ComponentList* MONS_OpenGLComponentList = NULL;
uint8_t MONS_OpenGLComponent = 0;
MONS_OpenGLStorage* MONS_OpenGLCompoentStorage = NULL;

MONS_DynamicLibrary* OpenGL32 = NULL;

MSBool MONS_InitComponentOpenGL(MONS_ComponentList* ComponentList)
{
  LOG("Initializ OpenGL",MONSOON_LOG_INFO,MONSOON_LOG_INIT);
  MONS_OpenGLComponentList = ComponentList;
  MONS_Component* OpenGL = &(MONS_OpenGLComponentList -> Components[MONS_OpenGLComponent]);
  OpenGL -> Storage = GetMemory(sizeof(MONS_OpenGLStorage));
  MONS_OpenGLCompoentStorage = OpenGL -> Storage;

  char* DLLPath = MONS_FindOpenGLDLL();

  OpenGL32 = MONS_LoadLibrary(DLLPath,0);
  if (!OpenGL32)
  {
    MONS_SetErrorCode(Make_Code(MONSOON_LOG_UNABLE_DO));
    LOG("Unable to Load %s",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO,DLLPath);
    return False;
  }

  MONS_LoadOpenGLCore();

  MONS_Window* Window = MONS_CreateWindow("Monsoon OpenGL Dummy Window",(MONS_Rect){100,100,100,100});
  if (!Window)
  {
    MONS_SetErrorCode(Make_Code(MONSOON_LOG_UNABLE_DO));
    LOG("Unable to Create OpenGL Dummy Window",MONSOON_LOG_ERROR,MONSOON_LOG_UNABLE_DO);
    return False;
  }

  MONS_OpenGLContext* Context = MONS_CreateBasicOpenGLContext(Window);
  MONS_MakeCurrentOpenGLContext(Context);

  MONS_LoadOpenGLFunctions();
  MONS_RemoveCurrentOpenGLContect();
  MONS_SetComponentInit(MONS_OpenGLComponentList,MONSOON_COMPONENT_OPENGL,True);
  LOG("Initialized OpenGL",MONSOON_LOG_INFO,MONSOON_LOG_INIT);

  return True;
}

MSBool MONS_DeInitComponentOpenGL()
{
  if (OpenGL32)
  {
    MONS_FreeLibrary(OpenGL32);
  }

  MONS_Component* OpenGL = &(MONS_OpenGLComponentList -> Components[MONS_OpenGLComponent]);
  if (OpenGL -> Storage)
  {
    RemoveMemory(OpenGL -> Storage);
  }
  MONS_OpenGLCompoentStorage = NULL;

  return False;
}

char* MONS_FindOpenGLDLL()
{
  char* DLLPath = NULL;

  #ifdef MONSOON_PLATFORM_NT
     DLLPath = MONS_FindFile("OpenGL32.DLL",NULL,True);
  #endif

  #ifdef MONSOON_PLATFORM_POSIX
     DLLPath = MONS_FindFile("libGL.so.1","/lib:/usr/lib:/usr/lib/x86_64-linux-gnu",True);
  #endif

  return DLLPath;
}

void* MONS_LoadOpenGLFunction(char* ProcName)
{
  void* address = glGetProcAddress(ProcName);
  if (!address)
  {
    address = MONS_GetProcAddress(ProcName, OpenGL32);
  }
  LOG("ProcName = %s,address = 0x%p",MONSOON_LOG_HIGHT_DEBUG,255,ProcName,address);
  return address;
}

MSBool MONS_LoadOpenGLCore()
{
  glGetProcAddress = (PFNWGLGETPROCADDRESSPROC)MONS_GetProcAddress(sglGetProcAddress,OpenGL32);
  glCreateContext = (PFNWGLCREATECONTEXTPROC)MONS_GetProcAddress(sglCreateContext,OpenGL32);
  glMakeCurrent = (PFNWGLMAKECURRENTPROC)MONS_GetProcAddress(sglMakeCurrent,OpenGL32);
  glDeleteContext = (PFNWGLDELETECONTEXTPROC)MONS_GetProcAddress(sglDeleteContext,OpenGL32);

  return True;
}

MSBool MONS_CreateDummyOpenGLContext(MONS_Window* Window)
{
  return True;
}

MSBool MONS_LoadOpenGLFunctions()
{
  glGetString                 = (PFNGLGETSTRINGPROC)MONS_LoadOpenGLFunction(sglGetString);
  glCreateContextAttribsARB   = (PFNWGLCREATECONTEXTATTRIBSARBPROC)MONS_LoadOpenGLFunction(sglCreateContextAttribsARB);
  glClearColor                = (PFNGLCLEARCOLORPROC)MONS_LoadOpenGLFunction(sglClearColor);
  glClear                     = (PFNGLCLEARPROC)MONS_LoadOpenGLFunction(sglClear);
  glClearColor                = (PFNGLCLEARCOLORPROC)MONS_LoadOpenGLFunction(sglClearColor);
  glCreateShader              = (PFNGLCREATESHADERPROC)MONS_LoadOpenGLFunction(sglCreateShader);
  glShaderSource              = (PFNGLSHADERSOURCEPROC)MONS_LoadOpenGLFunction(sglShaderSource);
  glGetShaderiv               = (PFNGLGETSHADERIVPROC)MONS_LoadOpenGLFunction(sglGetShaderiv);
  glGetShaderInfoLog          = (PFNGLGETSHADERINFOLOGPROC)MONS_LoadOpenGLFunction(sglGetShaderInfoLog);
  glCreateProgram             = (PFNGLCREATEPROGRAMPROC)MONS_LoadOpenGLFunction(sglCreateProgram);
  glAttachShader              = (PFNGLATTACHSHADERPROC)MONS_LoadOpenGLFunction(sglAttachShader);
  glLinkProgram               = (PFNGLLINKPROGRAMPROC)MONS_LoadOpenGLFunction(sglLinkProgram);
  glGetProgramiv              = (PFNGLGETPROGRAMIVPROC)MONS_LoadOpenGLFunction(sglGetProgramiv);
  glGetProgramInfoLog         = (PFNGLGETPROGRAMINFOLOGPROC)MONS_LoadOpenGLFunction(sglGetProgramInfoLog);
  glGenBuffers                = (PFNGLGENBUFFERSPROC)MONS_LoadOpenGLFunction(sglGenBuffers);
  glBindBuffer                = (PFNGLBINDBUFFERPROC)MONS_LoadOpenGLFunction(sglBindBuffer);
  glBufferData                = (PFNGLBUFFERDATAPROC)MONS_LoadOpenGLFunction(sglBufferData);
  glEnableVertexAttribArray   = (PFNGLENABLEVERTEXATTRIBARRAYPROC)MONS_LoadOpenGLFunction(sglEnableVertexAttribArray);
  glVertexAttribPointer       = (PFNGLVERTEXATTRIBPOINTERPROC)MONS_LoadOpenGLFunction(sglVertexAttribPointer);
  glBindVertexArray           = (PFNGLBINDVERTEXARRAYPROC)MONS_LoadOpenGLFunction(sglBindVertexArray);
  glGenVertexArrays           = (PFNGLGENVERTEXARRAYSPROC)MONS_LoadOpenGLFunction(sglGenVertexArrays);
  glDrawElements              = (PFNGLDRAWELEMENTSPROC)MONS_LoadOpenGLFunction(sglDrawElements);
  glUseProgram                = (PFNGLUSEPROGRAMPROC)MONS_LoadOpenGLFunction(sglUseProgram);
  glCompileShader             = (PFNGLCOMPILESHADERPROC)MONS_LoadOpenGLFunction(sglCompileShader);
  glPolygonMode               = (PFNGLPOLYGONMODEPROC)MONS_LoadOpenGLFunction(sglPolygonMode);
  glGetUniformLocation        = (PFNGLGETUNIFORMLOCATIONPROC)MONS_LoadOpenGLFunction(sglGetUniformLocation);
  glUniform1f                 = (PFNGLUNIFORM1FPROC)MONS_LoadOpenGLFunction(sglUniform1f);
  glDeleteShader              = (PFNGLDELETESHADERPROC)MONS_LoadOpenGLFunction(sglDeleteShader);
  glDeleteProgram             = (PFNGLDELETEPROGRAMPROC)MONS_LoadOpenGLFunction(sglDeleteProgram);
  glGetProgramInterfaceiv     = (PFNGLGETPROGRAMINTERFACEIVPROC)MONS_LoadOpenGLFunction(sglGetProgramInterfaceiv);
  glGetProgramResourceiv      = (PFNGLGETPROGRAMRESOURCEIVPROC)MONS_LoadOpenGLFunction(sglGetProgramResourceiv);
  glGetProgramResourceName    = (PFNGLGETPROGRAMRESOURCENAMEPROC)MONS_LoadOpenGLFunction(sglGetProgramResourceName);
  glGetActiveUniform          = (PFNGLGETACTIVEUNIFORMPROC)MONS_LoadOpenGLFunction(sglGetActiveUniform);
  glUniform3f                 = (PFNGLUNIFORM3FPROC)MONS_LoadOpenGLFunction(sglUniform3f);
  glUniformMatrix4fv          = (PFNGLUNIFORMMATRIX4FVPROC)MONS_LoadOpenGLFunction(sglUniformMatrix4fv);
  glUniform2f                 = (PFNGLUNIFORM2FPROC)MONS_LoadOpenGLFunction(sglUniform2f);

  return True;
}

MSBool MONS_UnLoadOpenGLFunctions()
{
  glGetString                 = NULL;
  glCreateContextAttribsARB   = NULL;
  glClearColor                = NULL;
  glClear                     = NULL;
  glClearColor                = NULL;
  glCreateShader              = NULL;
  glShaderSource              = NULL;
  glGetShaderiv               = NULL;
  glGetShaderInfoLog          = NULL;
  glCreateProgram             = NULL;
  glAttachShader              = NULL;
  glLinkProgram               = NULL;
  glGetProgramiv              = NULL;
  glGetProgramInfoLog         = NULL;
  glGenBuffers                = NULL;
  glBindBuffer                = NULL;
  glBufferData                = NULL;
  glEnableVertexAttribArray   = NULL;
  glVertexAttribPointer       = NULL;
  glBindVertexArray           = NULL;
  glGenVertexArrays           = NULL;
  glDrawElements              = NULL;
  glUseProgram                = NULL;
  glCompileShader             = NULL;
  glPolygonMode               = NULL;
  glGetUniformLocation        = NULL;
  glUniform1f                 = NULL;
  glDeleteShader              = NULL;
  glDeleteProgram             = NULL;
  glGetProgramInterfaceiv     = NULL;
  glGetProgramResourceiv      = NULL;
  glGetProgramResourceName    = NULL;
  glGetActiveUniform          = NULL;
  glUniform3f                 = NULL;
  glUniformMatrix4fv          = NULL;
  glUniform2f                 = NULL;

  return True;
}
