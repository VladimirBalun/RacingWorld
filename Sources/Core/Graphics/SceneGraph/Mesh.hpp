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

namespace Core { namespace Graphics { namespace SceneGraph {

    class Mesh
    {
    public:
        Mesh() noexcept;
        Mesh(std::vector<float>&& elements, unsigned int count_elements) noexcept;
        void draw() const noexcept;
        ~Mesh();
    private:
        static const std::uint8_t ALIGNMENT_VERTEX = 0;
        static const std::uint8_t ALIGNMENT_TEXTURE_COORDINATE = 3;
        static const std::uint8_t ALIGNMENT_NORMAL = 5;
        static constexpr std::uint8_t SIZE_ELEMENT = ALIGNMENT_NORMAL + 3;
    private:
        std::vector<float> m_elements{};
        unsigned int m_vbo = 0;
        unsigned int m_vao = 0;
        unsigned int m_count_elements = 0;
    };

}}}
