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

in vec2 vs_out_texture_coordinate;

uniform vec3      fs_un_light_color;
uniform sampler2D fs_un_texture;

out vec4 fs_out_color;

void main()
{
	vec4 preapared_light_color = vec4(fs_un_light_color, 1.0f);
	fs_out_color = preapared_light_color * texture(fs_un_texture, vs_out_texture_coordinate);
}
