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

#pragma once

#include <string_view>

namespace Game::ID
{

    inline const std::string_view g_base_vert_shader_id = "base_shader_vert";
    inline const std::string_view g_font_vert_shader_id = "font_shader_vert";
    inline const std::string_view g_test_vert_shader_id = "test_shader_vert";

    inline const std::string_view g_base_frag_shader_id = "base_shader_frag";
    inline const std::string_view g_font_frag_shader_id = "font_shader_frag";
    inline const std::string_view g_test_frag_shader_id = "test_shader_frag";

    inline const char* g_background_sound = "background";

}
