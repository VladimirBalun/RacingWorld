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

#include <functional>
#include <unordered_map>
#include <boost/filesystem/convenience.hpp>

Core::Resources::MaterialSPtr Core::Resources::Material::Builder::build() const noexcept
{
    return nullptr;
       // std::make_shared<Material>(m_shininess, std::move(m_ambient_texture_name),
       // std::move(m_ambient_texture_name), std::move(m_ambient_texture_name));
}

Core::Resources::Material::Builder& Core::Resources::Material::Builder::setShininess(const float shininess) noexcept
{
    m_shininess = shininess;
    return *this;
}

Core::Resources::Material::Builder& Core::Resources::Material::Builder::setAmbientTextureName(std::string&& texture_name) noexcept
{
    m_ambient_texture_name = std::move(texture_name);
    return *this;
}

Core::Resources::Material::Builder& Core::Resources::Material::Builder::setDiffuseTextureName(std::string&& texture_name) noexcept
{
    m_diffuse_texture_name = std::move(texture_name);
    return *this;
}

Core::Resources::Material::Builder& Core::Resources::Material::Builder::setSpecularTextureName(std::string&& texture_name) noexcept
{
    m_specular_texture_name = texture_name;
    return *this;
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
    using MaterialLoader = std::function<bool(Material&, const std::string&)>;
    static const std::unordered_map<std::string, MaterialLoader> available_loaders = {
        { ".mtl", nullptr }
    };

    const std::string extension = boost::filesystem::extension(material_path);
    const auto it = available_loaders.find(extension); 
    if (it != end(available_loaders))
    {
        if (const MaterialLoader loader = it->second)
        {
            return loader(*this, material_path);
        }
    }

    return false;
}
