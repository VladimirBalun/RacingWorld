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

#include "../../ResourcesFWD.hpp"
#include "../../Resources/Model.hpp"

namespace Core::Graphics::SceneGraph
{

    class Node;
    class Mesh;
    class Scene;
    class Texture2D;

    class NodeBuilder
    {
    public:
        static std::shared_ptr<Node> build(Resources::ModelSPtr model, Scene& scene);
    private:
        static std::shared_ptr<Node> createNode(const Resources::Model::Object& object, Scene& scene);
    };

    class MeshBuilder
    {
    public:
        static const Mesh* build(const Resources::Model::Object& object, Scene& scene);
    private:
        static unsigned int getCountElements(std::size_t count_vertices) noexcept;
        static unsigned int getCountElements(std::vector<float>& elements) noexcept;
        static void addVec3ToElements(std::vector<float>& elements, const glm::vec3& vector);
        static void addVec2ToElements(std::vector<float>& elements, const glm::vec2& vector);
    };

    class TextureBuilder
    {
    public:
        static Texture2D build(Resources::ImageSPtr image);
    };

}
