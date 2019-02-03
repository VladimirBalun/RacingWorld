#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCoordinate;
layout (location = 3) in vec3 normal;

out vec3 fragmentColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
    fragmentColor = vec3(1.0f, 0.0f, 0.0f);
}