#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 ScreenMat;
uniform vec2 Coordinations;
uniform vec2 WidthAndHeight;

void main()
{
    vec2 p = aPos * WidthAndHeight + Coordinations;
    gl_Position = ScreenMat * vec4(p, 0.0, 1.0);
}

#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(0.2, 0.5, 0.2, 1.0);
}
