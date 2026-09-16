#include <Monsoon/Monsoon.h>
#include <Monsoon/Graphic/Graphic.h>

MSBool MONS_GL_BasicDrawRectangle(uint16_t WindowID,MONS_Rect* Rect,MONS_Rect* Colour)
{
  glUniformMatrix4fv(MONS_FindOpenGLUniformFromName(&, "ScreenMat") -> ID,1,False,(float*)WindowMat);
  glUniform2f(MONS_FindOpenGLUniformFromName(&Shader, "Coordinations") -> ID,CoordintionX,CoordintionY);
  glUniform2f(MONS_FindOpenGLUniformFromName(&Shader, "WidthAndHeight") -> ID,50.0f,50.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

  return True;
}

MSBool MONS_BasicDrawRectangle(uint16_t WindowID,MONS_Rect* Rect,MONS_Rect* Colour)
{
  MONS_BasicDrawContext* Context = MONS_GetBasicDrawContext(MONS_BASICDRAW_CONTEXT_RECTANGLE,WindowID);
  MONS_BasicDrawResource* MONS_GetBasicDrawResource(Context,);

  if (Context -> Window -> WindowArea.Height != Context -> Window -> WindowArea.Y)
  {
    
  }


  return True;
}
