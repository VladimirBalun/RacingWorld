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

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec2 vertexUV;

out vec2 fragmentUV;

void main() 
{
    fragmentUV = vertexUV;
    gl_Position.x = vertexPos.x*2 - 1;
    gl_Position.y = vertexPos.y*2 - 1;
    gl_Position.z = -1.0;
    gl_Position.w =  1.0;
}