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

#include <optional>

#include "Texture2D.hpp"
#include "../OpenGL.hpp"
#include "../../Math/Vectors/Vector3.hpp"

namespace Graphics { namespace Components {

    class Material 
    {
    public:
        explicit Material() noexcept = default;
        explicit Material(const Math::Vector3f& ambient, const Math::Vector3f& diffuse,
            const Math::Vector3f& specular, GLfloat shininess = 32.0f) noexcept
            : m_ambient_Color(ambient), m_diffuse_color(diffuse), m_specular_color(specular), m_shininess(shininess) {}
        explicit Material(const Math::Vector3f& ambient, const Math::Vector3f& diffuse,
            const Math::Vector3f& specular, const Texture2D& ambient_texture, const Texture2D& diffuse_texture, GLfloat shininess = 32.0f) noexcept
            : m_ambient_Color(ambient), m_diffuse_color(diffuse), m_specular_color(specular), m_ambient_texture(ambient_texture), m_diffuse_texture(diffuse_texture), m_shininess(shininess) {}
        GLvoid setAmbientColor(const Math::Vector3f& color) noexcept;
        GLvoid setDiffuseColor(const Math::Vector3f& color) noexcept;
        GLvoid setSpecularColor(const Math::Vector3f& color) noexcept;
        GLvoid setAmbientTexture(const Texture2D& ambient_texture) noexcept;
        GLvoid setDiffuseTexture(const Texture2D& diffuse_texture) noexcept;
        GLvoid setShininess(GLfloat shininess) noexcept;
        const Math::Vector3f& getAmbientColor() const noexcept;
        const Math::Vector3f& getDiffuseColor() const noexcept;
        const Math::Vector3f& getSpecularColor() const noexcept;
        const std::optional<Texture2D>& getAmbientTexture() const noexcept;
        const std::optional<Texture2D>& getDiffuseTexture() const noexcept;
        GLfloat getShininess() const noexcept;
    private:
        Math::Vector3f m_ambient_Color{};
        Math::Vector3f m_diffuse_color{};
        Math::Vector3f m_specular_color{};
        GLfloat m_shininess = 0.0f;
        std::optional<Texture2D> m_ambient_texture{};
        std::optional<Texture2D> m_diffuse_texture{};
    };

} }
