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

Graphics::SceneGraph::Node* Graphics::SceneGraph::SceneGraphBuilder::build() noexcept
{
    void* memoryForRootNode = mAllocator.allocate(sizeof(Node));
    Node* rootGroup = new (memoryForRootNode) Node();
    rootGroup->addChild(buildCubes());
    rootGroup->addChild(buildGround());
    rootGroup->addChild(buildTree());
    return rootGroup;
}

Graphics::SceneGraph::Node* Graphics::SceneGraph::SceneGraphBuilder::buildTree() noexcept
{
    void* memoryForGroupNode = mAllocator.allocate(sizeof(Node));
    Node* groupNode = new (memoryForGroupNode) Node();

    // TODO: temp material for geometry
    Components::Material groundMaterial(
        { 0.0f ,0.05f, 0.0 },
        { 0.4f, 0.5f, 0.4f },
        { 0.04f, 0.7f, 0.04f },
        0.078125f
    );

    Math::Matrix4x4f scaleTransformation{};
    Math::setScaleMatrix(scaleTransformation, { 0.3f, 0.3f, 0.3f });
    Math::Matrix4x4f grounTransformation{};
    Math::setTranslationMatrix(grounTransformation, { 1.0f,  -0.52f,  1.0f });
    grounTransformation.mul(scaleTransformation);
    void* memoryForGroundPolygon = mAllocator.allocate(sizeof(Node));
    Node* treeNode = new (memoryForGroundPolygon) Node();
    treeNode->setMesh(mMeshManager.getMesh(Managers::TREE));
    treeNode->setTransformation(grounTransformation);
    groupNode->addChild(treeNode);

    return groupNode;
}

Graphics::SceneGraph::Node* Graphics::SceneGraph::SceneGraphBuilder::buildCubes() noexcept
{
    void* memoryForGroupNode = mAllocator.allocate(sizeof(Node));
    Node* groupNode = new (memoryForGroupNode) Node();

    // TODO: temp geomerty for rendering
    Math::Vector3f cubePositions[COUNT_MODELS] = {
        Math::Vector3f(0.0f,  0.0f,  0.0f),
        Math::Vector3f(2.0f,  0.0f,  -5.0f),
        Math::Vector3f(-1.5f, 0.0f, -2.5f),
        Math::Vector3f(-3.8f, 0.0f, -7.3f),
        Math::Vector3f(2.4f,  0.0f, -3.5f),
        Math::Vector3f(-1.7f, 0.0f,  -7.5f),
        Math::Vector3f(1.3f,  0.0f, -2.5f),
        Math::Vector3f(1.5f,  0.0f,  -2.5f),
        Math::Vector3f(1.5f,  0.0f,  -1.5f),
        Math::Vector3f(-1.3f, 0.0f,  -1.5f)
    };

    // TODO: temp material for geometry
    Components::Material goldMaterial(
        { 0.24725f, 0.1995f, 0.0745f },
        { 0.75164f, 0.60648f, 0.22648f },
        { 0.628281f, 0.555802f, 0.366065f },
        0.4f
    );

    Components::Mesh& mesh = mMeshManager.getMesh(Managers::CUBE);
    mesh.setMaterial(goldMaterial);

    for (std::uint8_t i = 0; i < COUNT_MODELS; i++)
    {
        Math::Matrix4x4f cubeTransofrmation{};
        Math::setTranslationMatrix(cubeTransofrmation, cubePositions[i]);
        void* memoryForCubeNode = mAllocator.allocate(sizeof(Node));
        Node* cubeNode = new (memoryForCubeNode) Node();
        cubeNode->setMesh(mesh);
        cubeNode->setTransformation(cubeTransofrmation);
        groupNode->addChild(cubeNode);
    }

    return groupNode;
}

Graphics::SceneGraph::Node* Graphics::SceneGraph::SceneGraphBuilder::buildGround() noexcept
{
    void* memoryForGroupNode = mAllocator.allocate(sizeof(Node));
    Node* groupNode = new (memoryForGroupNode) Node();

    // TODO: temp material for geometry
    Components::Material groundMaterial(
        { 0.0f ,0.05f, 0.0 },
        { 0.4f, 0.5f, 0.4f },
        { 0.04f, 0.7f, 0.04f },
        0.078125f
    );
 
    Components::Mesh& mesh = mMeshManager.getMesh(Managers::GROUND_POLYGON);
    mesh.setMaterial(groundMaterial);

    Math::Matrix4x4f scaleTransformation{};
    Math::setScaleMatrix(scaleTransformation, { 5.0f, 0.0f, 5.0f });
    for (GLfloat x = -5.0; x < 10; x++)
    {
        for (GLfloat z = 5.0; z > -10; z--)
        {
            Math::Matrix4x4f grounTransformation{};
            Math::setTranslationMatrix(grounTransformation, { x, -0.5f, z });
            grounTransformation.mul(scaleTransformation);
            void* memoryForGroundPolygon = mAllocator.allocate(sizeof(Node));
            Node* groundNode = new (memoryForGroundPolygon) Node();
            groundNode->setMesh(mesh);
            groundNode->setTransformation(grounTransformation);
            groupNode->addChild(groundNode);
        }
    }

    return groupNode;
}
