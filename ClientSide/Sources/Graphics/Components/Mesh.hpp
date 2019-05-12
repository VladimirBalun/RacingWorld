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

#include "Material.hpp"
#include "../OpenGL.hpp"
#include "../../Math/Vectors.hpp"

namespace Graphics { namespace Components {

    class Mesh
    {
    public:
        explicit Mesh() noexcept = default;
        explicit Mesh(const GLfloat* elements, GLuint count_elements) noexcept;
        GLvoid setMaterial(const Material& material) noexcept;
        const std::optional<Material>& getMaterial() const noexcept;
        GLvoid destroy() const noexcept;
        GLvoid draw() const noexcept;
    public:
        static const std::uint8_t ALIGNMENT_VERTEX = 0;
        static const std::uint8_t ALIGNMENT_TEXTURE_COORDINATE = 3;
        static const std::uint8_t ALIGNMENT_NORMAL = 5;
        static constexpr std::uint8_t SIZE_ELEMENT = ALIGNMENT_NORMAL + 3;
    private:
        GLuint m_vbO = 0;
        GLuint m_vao = 0;
        GLuint m_count_elements = 0;
        const GLfloat* m_elements = nullptr;
        std::optional<Material> m_material{};
    };

}}
