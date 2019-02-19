#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordianate;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentNormal;
out vec3 fragmentPosition;

void main()
{
    fragmentNormal = normal;
    fragmentPosition = vec3(modelMatrix * vec4(position, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}
