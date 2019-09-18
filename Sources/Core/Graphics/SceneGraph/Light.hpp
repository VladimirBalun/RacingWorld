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

#include <glm/vec3.hpp>

namespace Core { namespace Resources { namespace SceneGraph {

    class Light
    {
    public:
        Light() noexcept = default;
        Light(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) noexcept
            : m_position(position), m_ambient_color(ambient), m_diffuse_color(diffuse), m_specular_color(specular) {}
        void move(const glm::vec3& alignment) noexcept;
        const glm::vec3& getPosition() const noexcept;
        const glm::vec3& getAmbientColor() const noexcept;
        const glm::vec3& getDiffuseColor() const noexcept;
        const glm::vec3& getSpecularColor() const noexcept;
    private:
        glm::vec3 m_position{};
        glm::vec3 m_ambient_color{};
        glm::vec3 m_diffuse_color{};
        glm::vec3 m_specular_color{};
    };

}}}
