#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fragColor;

void main()
{
  //  vec3 color = vec3 (0.0f, 1.0f, 0.0f);
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    fragColor = color;
}