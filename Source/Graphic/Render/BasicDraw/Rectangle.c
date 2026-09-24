














#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>
#include <cglm/cglm.h>

MSBool MONS_GL_LoadBasicDrawReactangleResources(MONS_BasicDrawContext* Context)
{
  MONS_BasicDrawTargetResourceRectangle* RectangleResources = (Context -> TargetResources[MONS_BASICDRAE_RENDERTARGET_RECTANGLE]);

  glm_ortho(
    0,
    Context -> Window -> WindowArea.Width,
    Context -> Window -> WindowArea.Height,
    0,
    -1.0f,
    1.0,
    RectangleResources -> ScreenMat
  );
  
  return True;
}

MSBool MONS_GL_BasicDrawRectangle(MONS_BasicDrawContext* Context,MONS_Rect Rect,MONS_Rect* Colour)
{
  MONS_BasicDrawTargetResourceRectangle* Target = (Context -> TargetResources[MONS_BASICDRAE_RENDERTARGET_RECTANGLE]);
  MONS_OpenGLShader* Shader = ((MONS_GL_BasicDrawTargetResourceRectangle*)Target -> Resource) -> Shader;

  glUniformMatrix4fv(MONS_FindOpenGLUniformFromName(Shader, "ScreenMat") -> ID,1,False,(float*)Target -> ScreenMat);
  glUniform2f(MONS_FindOpenGLUniformFromName(Shader, "Coordinations") -> ID,Rect.X,Rect.Y);
  glUniform2f(MONS_FindOpenGLUniformFromName(Shader, "WidthAndHeight") -> ID,Rect.Width,Rect.Height);
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

  return True;
}

MSBool MONS_BasicDrawRectangle(uint16_t ContextID,MONS_Rect* Rect,MONS_Rect* Colour)
{
  MONS_BasicDrawStorage* Storage = MONS_Components -> Components[MONS_BasicDrawComponent].Storage;
  if (!MONS_CheckBasicDrawContextCache(ContextID))
  {
    return False;
  }

  MONS_GL_BasicDrawRectangle(Storage -> LastUsedContext, *Rect, Colour);

  return True;
}
