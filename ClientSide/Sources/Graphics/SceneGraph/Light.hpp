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

#include "../OpenGL.hpp"
#include "../../Math/Vectors/Vector3.hpp"

namespace Graphics { namespace SceneGraph {

    class Light
    {
    public:
        explicit Light(const Math::Vector3<GLfloat>& position, const Math::Vector3<GLfloat>& ambient,
            const Math::Vector3<GLfloat>& diffuse, const Math::Vector3<GLfloat>& specular = { 1.0, 1.0f, 1.0f }) noexcept
            : m_position(position), m_ambient_color(ambient), m_diffuse_color(diffuse), m_specular_color(specular) {}
        GLvoid move(Math::Vector3f&& alignment) noexcept;
        const Math::Vector3f& getPosition() const noexcept;
        const Math::Vector3f& getAmbientColor() const noexcept;
        const Math::Vector3f& getDiffuseColor() const noexcept;
        const Math::Vector3f& getSpecularColor() const noexcept;
    private:
        Math::Vector3f m_position;
        Math::Vector3f m_ambient_color;
        Math::Vector3f m_diffuse_color;
        Math::Vector3f m_specular_color;
    };

} }
