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

#include "SceneGraphBuilder.hpp"

#define COUNT_MODELS 10

Graphics::SceneGraph::Node* Graphics::SceneGraph::SceneGraphBuilder::build(Managers::MeshManager& meshManager, Memory::Allocators::LinearAllocator& allocator) noexcept
{
    void* memoryForRootNode = allocator.allocate(sizeof(Node));
    Node* rootNode = new (memoryForRootNode) Node;

    // TODO: temp geomerty for rendering
    Math::Vector3f cubePositions[COUNT_MODELS] = {
        Math::Vector3f(0.0f,  0.0f,  0.0f),
        Math::Vector3f(2.0f,  5.0f,  -15.0f),
        Math::Vector3f(-1.5f, -2.2f, -2.5f),
        Math::Vector3f(-3.8f, -2.0f, -12.3f),
        Math::Vector3f(2.4f,  -0.4f, -3.5f),
        Math::Vector3f(-1.7f, 3.0f,  -7.5f),
        Math::Vector3f(1.3f,  -2.0f, -2.5f),
        Math::Vector3f(1.5f,  2.0f,  -2.5f),
        Math::Vector3f(1.5f,  0.2f,  -1.5f),
        Math::Vector3f(-1.3f, 1.0f,  -1.5f)
    };

    // TODO: temp material for geometry
    Components::Material goldMaterial(
        { 0.24725f, 0.1995f, 0.0745f },
        { 0.75164f, 0.60648f, 0.22648f },
        { 0.628281f, 0.555802f, 0.366065f },
        0.4f
    );

    Components::Mesh& mesh = meshManager.getMesh(Managers::CUBE);
    mesh.setMaterial(goldMaterial);

    for (std::uint8_t i = 0; i < COUNT_MODELS; i++)
    {
        Math::Matrix4x4f cubeTransofrmation;
        Math::setTranslationMatrix(cubeTransofrmation, cubePositions[i]);
        void* memoryForCubeNode = allocator.allocate(sizeof(Node));
        Node* cubeNode = new (memoryForCubeNode) Node;
        cubeNode->setMesh(mesh);
        cubeNode->setTransformation(cubeTransofrmation);
        rootNode->addChild(cubeNode);
    }

    return rootNode;
}
