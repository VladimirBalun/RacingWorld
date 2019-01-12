#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 gWorldPerspectiv;
uniform mat4 gWorldPos;
uniform mat4 gWorldRot;

//uniform float gScale;

out vec3 fragColor;

void main()
{
   gl_Position = gWorldPerspectiv * gWorldPos * gWorldRot * vec4(position, 1.0);
    fragColor = color;
}