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
#include "MeshBuilder.hpp"

#include "Mesh.hpp"

Core::Graphics::SceneGraph::Mesh Core::Graphics::SceneGraph::MeshBuilder::build(Resources::Model::Mesh* input_mesh)
{
    const std::vector<unsigned int>& indices = input_mesh->getIndices();
    const std::vector<Resources::Model::Vertex>& vertices = input_mesh->getVertices();
    std::vector<float> output_elements{};
    output_elements.reserve(getCountElements(vertices.size()));
    for (const auto index : indices)
    {
        const Resources::Model::Vertex& vertex = vertices.at(index);
        const glm::vec3& normal = vertex.getNormal();
        const glm::vec3& position = vertex.getPosition();
        const glm::vec2& texture_coordinate = vertex.getTextureCoordinate();

        addVec3ToElements(output_elements, position);
        addVec3ToElements(output_elements, normal);
        addVec2ToElements(output_elements, texture_coordinate);
    }

    const unsigned int count_elements = getCountElements(output_elements);
    return Mesh(std::move(output_elements), count_elements);
}

unsigned Core::Graphics::SceneGraph::MeshBuilder::getCountElements(std::size_t count_vertices) noexcept
{
    return count_vertices * COUNT_ELEMS_IN_VERTEX;
}

unsigned int Core::Graphics::SceneGraph::MeshBuilder::getCountElements(std::vector<float>& elements) noexcept
{
    return elements.size() / COUNT_ELEMS_IN_VERTEX;
}

void Core::Graphics::SceneGraph::MeshBuilder::addVec3ToElements(std::vector<float>& elements, const glm::vec3& vector)
{
    elements.push_back(vector.x);
    elements.push_back(vector.y);
    elements.push_back(vector.z);
}

void Core::Graphics::SceneGraph::MeshBuilder::addVec2ToElements(std::vector<float>& elements, const glm::vec2& vector)
{
    elements.push_back(vector.x);
    elements.push_back(vector.y);
}
