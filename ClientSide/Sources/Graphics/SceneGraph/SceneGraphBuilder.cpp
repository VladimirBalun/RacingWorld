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

std::shared_ptr<Graphics::SceneGraph::Node> Graphics::SceneGraph::SceneGraphBuilder::build() noexcept
{
    std::shared_ptr<Node> root_group = std::make_shared<Node>();
    root_group->addChild(buildCubes());
    root_group->addChild(buildGround());
    root_group->addChild(buildTree());
    return root_group;
}

std::shared_ptr<Graphics::SceneGraph::Node> Graphics::SceneGraph::SceneGraphBuilder::buildTree() noexcept
{
    std::shared_ptr<Node> group_node = std::make_shared<Node>();

    Components::Mesh& tree_mesh = m_mesh_manager.getMesh(Managers::TREE);
    tree_mesh.setMaterial(Components::Material{
        { 0.0f ,0.05f, 0.0 },
        { 0.4f, 0.5f, 0.4f },
        { 0.04f, 0.7f, 0.04f },
        0.078125f
    });

    Math::Matrix4x4f scale_transformation{};
    Math::setScaleMatrix(scale_transformation, { 0.3f, 0.3f, 0.3f });
    Math::Matrix4x4f tree_transformation{};
    Math::setTranslationMatrix(tree_transformation, { 1.0f,  -0.52f,  1.0f });
    tree_transformation.mul(scale_transformation);
    std::shared_ptr<Node> tree_node = std::make_shared<Node>();
    tree_node->setMesh(tree_mesh);
    tree_node->setTransformation(tree_transformation);
    group_node->addChild(tree_node);

    return group_node;
}

std::shared_ptr<Graphics::SceneGraph::Node> Graphics::SceneGraph::SceneGraphBuilder::buildCubes() noexcept
{
    std::shared_ptr<Node> group_node = std::make_shared<Node>();

    // TODO: temp geomerty positions for rendering
    Math::Vector3f cube_positions[COUNT_MODELS] = {
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

    Components::Mesh& cube_mesh = m_mesh_manager.getMesh(Managers::CUBE);
    cube_mesh.setMaterial(Components::Material{
        { 0.24725f, 0.1995f, 0.0745f },
        { 0.75164f, 0.60648f, 0.22648f },
        { 0.628281f, 0.555802f, 0.366065f },
        0.4f
    });

    for (std::uint8_t i = 0; i < COUNT_MODELS; i++)
    {
        Math::Matrix4x4f cube_transofrmation{};
        Math::setTranslationMatrix(cube_transofrmation, cube_positions[i]);
        std::shared_ptr<Node> cube_node = std::make_shared<Node>();
        cube_node->setMesh(cube_mesh);
        cube_node->setTransformation(cube_transofrmation);
        group_node->addChild(cube_node);
    }

    return group_node;
}

std::shared_ptr<Graphics::SceneGraph::Node> Graphics::SceneGraph::SceneGraphBuilder::buildGround() noexcept
{
    std::shared_ptr<Node> group_node = std::make_shared<Node>();
 
    Components::Mesh& ground_mesh = m_mesh_manager.getMesh(Managers::GROUND_POLYGON);
    ground_mesh.setMaterial(Components::Material{
        { 0.0f ,0.05f, 0.0 },
        { 0.4f, 0.5f, 0.4f },
        { 0.04f, 0.7f, 0.04f },
        0.078125f
    });

    Math::Matrix4x4f scale_transformation{};
    Math::setScaleMatrix(scale_transformation, { 5.0f, 0.0f, 5.0f });
    for (GLfloat x = -5.0; x < 10; x++)
    {
        for (GLfloat z = 5.0; z > -10; z--)
        {
            Math::Matrix4x4f ground_transformation{};
            Math::setTranslationMatrix(ground_transformation, { x, -0.5f, z });
            ground_transformation.mul(scale_transformation);
            std::shared_ptr<Node> ground_node = std::make_shared<Node>();
            ground_node->setMesh(ground_mesh);
            ground_node->setTransformation(ground_transformation);
            group_node->addChild(ground_node);
        }
    }

    return group_node;
}
