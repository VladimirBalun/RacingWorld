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

#include "Model.hpp"

#include "Loaders/ModelLoader.hpp"

const std::vector<glm::vec3>& Core::Resources::Model::getNormals() const noexcept
{
    return m_normals;
}

const std::vector<glm::vec3>& Core::Resources::Model::getVertices() const noexcept
{
    return m_vertices;
}

const std::vector<glm::vec2>& Core::Resources::Model::getTextureCoordinates() const noexcept
{
    return m_texture_coordinates;
}

bool Core::Resources::Model::load(const std::string& model_path) noexcept
{
    return Loaders::OBJLoader::load(*this, model_path);
}
