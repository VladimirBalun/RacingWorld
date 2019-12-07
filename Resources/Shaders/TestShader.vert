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

layout (location = 0) in vec3 vs_in_position;
layout (location = 1) in vec2 vs_in_texture_coordinate;
layout (location = 2) in vec3 vs_in_normal;

uniform mat4 vs_un_model;
uniform mat4 vs_un_view;
uniform mat4 vs_un_projection;

out vec2 vs_out_texture_coordinate;

void main()
{
     gl_Position = vs_un_projection * vs_un_view * vs_un_model * vec4(vs_in_position, 1.0);
	 vs_out_texture_coordinate = vec2(vs_in_texture_coordinate.x, vs_in_texture_coordinate.y);
}
