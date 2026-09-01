#ifndef MONSOON_GRAPGIC_API_OPENGL_SHADER_H
#define MONSOON_GRAPGIC_API_OPENGL_SHADER_H
#include <Monsoon/Monsoon.h>

//Compile OpenGL GLSL Shader Source
//------------------------------------------------------------------------------
//`Shader`:The Shader Object
//`VertextSource`:The Vertext Shader Source
//`FragmentSource`:The Fragment Shader Source
//------------------------------------------------------------------------------
//`The` VertextSource and FragmentSource will add to the Shader Object which was pass in
//`The` Shader Handle Will also be add to Shader Object
MONS_API MSBool MONS_CompileOpenGLShader(MONS_OpenGLShader* Shader,char* VertextSource,char* FragmentSource);

//Create a OpenGL Shader Programe and Link it together
//------------------------------------------------------------------------------
//`Shader`:The Shader Object
//------------------------------------------------------------------------------
//`The` Vertext and Fragment Shader must Compile Before Linking
MONS_API MSBool MONS_CreateAndLinkOpenGLShaderProgram(MONS_OpenGLShader* Shader);

MONS_API MSBool MONS_FreeOpenGLShader(MONS_OpenGLShader* Shader);

#endif
