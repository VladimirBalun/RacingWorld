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

#include "Material.hpp"

GLvoid Graphics::Components::Material::setAmbientColor(const Math::Vector3f& color) noexcept
{
    m_ambient_Color = color;
}

GLvoid Graphics::Components::Material::setDiffuseColor(const Math::Vector3f& color) noexcept
{
    m_diffuse_color = color;
}

GLvoid Graphics::Components::Material::setSpecularColor(const Math::Vector3f& color) noexcept
{
    m_specular_color = color;
}

GLvoid Graphics::Components::Material::setShininess(GLfloat shininess) noexcept
{
    m_shininess = shininess;
}

GLvoid Graphics::Components::Material::setAmbientTexture(const Texture2D& ambient_texture) noexcept
{
    m_ambient_texture = ambient_texture;
}

GLvoid Graphics::Components::Material::setDiffuseTexture(const Texture2D& diffuse_texture) noexcept
{
    m_diffuse_texture = diffuse_texture;
}

const Math::Vector3<GLfloat>& Graphics::Components::Material::getAmbientColor() const noexcept
{
    return m_ambient_Color;
}

const Math::Vector3<GLfloat>& Graphics::Components::Material::getDiffuseColor() const noexcept
{
    return m_diffuse_color;
}

const Math::Vector3<GLfloat>& Graphics::Components::Material::getSpecularColor() const noexcept
{
    return m_specular_color;
}

const std::optional<Graphics::Components::Texture2D>& Graphics::Components::Material::getAmbientTexture() const noexcept
{
    return m_ambient_texture;
}

const std::optional<Graphics::Components::Texture2D>& Graphics::Components::Material::getDiffuseTexture() const noexcept
{
    return m_diffuse_texture;
}

GLfloat Graphics::Components::Material::getShininess() const noexcept
{
    return m_shininess;
}
