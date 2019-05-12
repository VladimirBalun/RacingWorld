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

#include <vector>

#include "../OpenGL.hpp"

namespace Graphics { namespace Components {

    class Texture2D
    {
    public:
        explicit Texture2D() noexcept = default;
        explicit Texture2D(const std::vector<char>&& image_data, GLuint width, GLuint height) noexcept;
        GLuint getID() const noexcept;
        GLuint getWidth() const noexcept;
        GLuint getHeight() const noexcept;
    private:
        GLuint m_width = 0;
        GLuint m_height = 0;
        GLuint m_texture_idD = 0;
    };

}}
