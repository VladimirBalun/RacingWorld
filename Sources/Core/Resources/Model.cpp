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

#pragma region Vertex

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

#pragma endregion

#pragma region Object

Core::Resources::Model::Object::Object(std::size_t count_vertices, std::size_t count_indices) noexcept
{
    m_indices.reserve(count_indices);
    m_vertices.reserve(count_vertices);
}

void Core::Resources::Model::Object::addIndex(unsigned int index) noexcept
{
    m_indices.push_back(index);
}

void Core::Resources::Model::Object::setName(const std::string & name) noexcept
{
    m_name = name;
}

void Core::Resources::Model::Object::setMaterialName(const std::string& name) noexcept
{
    m_material_name = name;
}

const std::string & Core::Resources::Model::Object::getName() const noexcept
{
    return m_name;
}

const std::string& Core::Resources::Model::Object::getMaterialName() const noexcept
{
    return m_material_name;
}

const std::vector<Core::Resources::Model::Vertex>& Core::Resources::Model::Object::getVertices() const noexcept
{
    return m_vertices;
}

const std::vector<unsigned int>& Core::Resources::Model::Object::getIndices() const noexcept
{
    return m_indices;
}

#pragma endregion

#pragma region Model

Core::Resources::Model::Model(std::size_t count_objects) noexcept
{
    m_objects.reserve(count_objects);
}

void Core::Resources::Model::addObject(Object&& object)
{
    m_objects.push_back(std::move(object));
}

const std::vector<Core::Resources::Model::Object>& Core::Resources::Model::getObjects() const noexcept
{
    return m_objects;
}

bool Core::Resources::Model::load(std::string_view model_path) noexcept
{
    return Loaders::OBJLoader::load(*this, model_path);
}

#pragma endregion