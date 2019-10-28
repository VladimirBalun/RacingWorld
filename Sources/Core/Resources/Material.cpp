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

#include "PrecompiledHeader.hpp"
#include "Material.hpp"

void Core::Resources::Material::setShininess(const float shininess) noexcept
{
    m_shininess = shininess;
}

void Core::Resources::Material::setAmbientTextureName(std::string&& texture_name) noexcept
{
    m_ambient_texture_name = std::move(texture_name);
}

void Core::Resources::Material::setDiffuseTextureName(std::string&& texture_name) noexcept
{
    m_diffuse_texture_name = std::move(texture_name);
}

void Core::Resources::Material::setSpecularTextureName(std::string&& texture_name) noexcept
{
    m_specular_texture_name = texture_name;
}

float Core::Resources::Material::getShininess() const noexcept
{
    return m_shininess;
}

const std::string& Core::Resources::Material::getAmbientTextureName() const noexcept
{
    return m_ambient_texture_name;
}

const std::string& Core::Resources::Material::getDiffuseTextureName() const noexcept
{
    return m_diffuse_texture_name;
}

const std::string& Core::Resources::Material::getSpecularTextureName() const noexcept
{
    return m_specular_texture_name;
}

bool Core::Resources::Material::load(const std::string& material_path) noexcept
{
    /*
     * At the moment, materials are loading in the 'ModelLoader',
     * with special function of the 'ResourceManager' for it.
     * Maybe later, material will be able to load without 'ModelLoader'.
     */

    return false;
}
