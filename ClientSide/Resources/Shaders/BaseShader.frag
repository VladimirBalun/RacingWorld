/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#version 330 core

struct Material 
{
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
}; 

struct Light
{
    vec3 position;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
};

in vec3 fragmentNormal;
in vec3 fragmentPosition;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

out vec4 fragmentColor;

void main()
{
    // Ambient color
    vec3 ambientColor = light.ambientColor * material.ambientColor;

    // Diffuse color 
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(light.position - fragmentPosition);
    vec3 diffuseColor  = light.diffuseColor * (max(dot(normal, lightDirection), 0.0) * material.diffuseColor);

    // Specular color
    vec3 viewDir = normalize(viewPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 specularColor = light.specularColor * (pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess) * material.specularColor);

    fragmentColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}
