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
#include "Model.hpp"

#include "Loaders/ModelLoader.hpp"

const glm::vec3& Core::Resources::Model::Vertex::getNormal() const noexcept
{
    return m_normal;
}

const glm::vec3& Core::Resources::Model::Vertex::getPosition() const noexcept
{
    return m_position;
}

const glm::vec2& Core::Resources::Model::Vertex::getTextureCoordinate() const noexcept
{
    return m_texture_coordinate;
}

Core::Resources::Model::Mesh::Mesh(std::size_t count_vertices, std::size_t count_indices) noexcept
{
    m_indices.reserve(count_indices);
    m_vertices.reserve(count_vertices);
}

void Core::Resources::Model::Mesh::addIndex(unsigned index)
{
    m_indices.push_back(index);
}

void Core::Resources::Model::Mesh::setMaterialName(const std::string& name) noexcept
{
    m_material_name = name;
}

const std::string Core::Resources::Model::Mesh::getMaterialName() const noexcept
{
    return m_material_name;
}

const std::vector<Core::Resources::Model::Vertex>& Core::Resources::Model::Mesh::getVertices() const noexcept
{
    return m_vertices;
}

const std::vector<unsigned int>& Core::Resources::Model::Mesh::getIndices() const noexcept
{
    return m_indices;
}

Core::Resources::Model::Model(std::size_t count_meshes) noexcept
{
    m_meshes.reserve(count_meshes);
}

void Core::Resources::Model::addMesh(const std::string& name, Mesh&& mesh)
{
    m_meshes.emplace(name, mesh);
}

bool Core::Resources::Model::isExistMeshByName(const std::string& name) const noexcept
{
    const auto it = m_meshes.find(name);
    return it != end(m_meshes);
}

const Core::Resources::Model::Mesh* Core::Resources::Model::getMeshByName(const std::string& name) const noexcept
{
    const auto it = m_meshes.find(name);
    if (it != end(m_meshes))
    {
        return &it->second;
    }

    return nullptr;
}

Core::Resources::Model::meshes_t::const_iterator Core::Resources::Model::meshesBegin() const noexcept
{
    return m_meshes.begin();
}

Core::Resources::Model::meshes_t::const_iterator Core::Resources::Model::meshesEnd() const noexcept
{
    return m_meshes.end();
}

bool Core::Resources::Model::load(const std::string& model_path) noexcept
{
    return Loaders::OBJLoader::load(*this, model_path);
}
