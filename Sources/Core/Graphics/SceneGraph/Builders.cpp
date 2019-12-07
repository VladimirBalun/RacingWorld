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
#include "Builders.hpp"

#include "Node.hpp"
#include "Mesh.hpp"
#include "Texture2D.hpp"
#include "../../Resources/Image.hpp"
#include "../../Managers/ResourceManager.hpp"

#pragma region NodeBuilder

Core::Graphics::SceneGraph::NodeSPtr Core::Graphics::SceneGraph::NodeBuilder::build(Resources::ModelSPtr model)
{
    if (model)
    {
        if (model->isSingleObject())
        {
            const Resources::Model::Object* object = &model->objectsBegin()->second;
            return createNode(object);
        }

        if (!model->isEmpty())
        {
            auto group = std::make_shared<Node>();
            for (auto it = model->objectsBegin(); it != model->objectsEnd(); ++it)
            {
                const Resources::Model::Object* object = &it->second;
                NodeSPtr node = createNode(object);
                group->addChild(node);
            }
            return group;
        }
    }

    return nullptr;
}

Core::Graphics::SceneGraph::NodeSPtr Core::Graphics::SceneGraph::NodeBuilder::createNode(const Resources::Model::Object* object)
{
    static Mesh mesh = MeshBuilder::build(object);
    auto node = std::make_shared<Node>();
    node->setMesh(&mesh);
    return node;
}

#pragma endregion

#pragma region MeshBuilder

constexpr std::uint8_t COUNT_ELEMS_IN_POS = 3u;
constexpr std::uint8_t COUNT_ELEMS_IN_NORMAL = 3u;
constexpr std::uint8_t COUNT_ELEMS_IN_TEXTURE_COORDINATE = 2u;
constexpr std::uint8_t COUNT_ELEMS_IN_VERTEX = COUNT_ELEMS_IN_POS + COUNT_ELEMS_IN_NORMAL + COUNT_ELEMS_IN_TEXTURE_COORDINATE;

Core::Graphics::SceneGraph::Mesh Core::Graphics::SceneGraph::MeshBuilder::build(const Resources::Model::Object* object)
{
    const std::vector<unsigned int>& indices = object->getIndices();
    const std::vector<Resources::Model::Vertex>& vertices = object->getVertices();

    std::vector<float> output_elements{};
    output_elements.reserve(getCountElements(vertices.size()));
    for (const auto index : indices)
    {
        const Resources::Model::Vertex& vertex = vertices.at(index);
        const glm::vec3& normal = vertex.getNormal();
        const glm::vec3& position = vertex.getPosition();
        const glm::vec2& texture_coordinate = vertex.getTextureCoordinate();

        // Necessary order of the following operations
        addVec3ToElements(output_elements, position);
        addVec3ToElements(output_elements, normal);
        addVec2ToElements(output_elements, texture_coordinate);
    }

    Texture2D texture;
    auto material = g_resource_manager.getResource<Resources::Material>(STR(object->getMaterialName()));
    if (material)
    {
        std::string_view diffuse_texture_name = material->getDiffuseTextureName();
        if (!diffuse_texture_name.empty())
        {
            std::shared_ptr<Resources::Image> image = g_resource_manager.getResource<Resources::Image>(STR(diffuse_texture_name));
            texture = TextureBuilder::build(image);
        }
    }

    const unsigned int count_elements = getCountElements(output_elements);
    return Mesh(texture, std::move(output_elements), count_elements);
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

#pragma endregion

#pragma region TextureBuilder

Core::Graphics::SceneGraph::Texture2D Core::Graphics::SceneGraph::TextureBuilder::build(Resources::ImageSPtr image)
{
    if (image)
    {
        const std::uint16_t texture_width = image->getWidth();
        const std::uint16_t texture_height = image->getHeight();
        const unsigned char* texture_data = image->getData();
        return Texture2D(texture_width, texture_height, texture_data);
    }

    return Texture2D{};
}

#pragma endregion
