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

#include "MeshManager.hpp"

GLvoid Graphics::Managers::MeshManager::initializeMeshes() noexcept
{
    //m_meshes[TREE] = createMesh("/Tree/Tree.obj");
    m_meshes[CUBE] = createMesh("/Cube.obj");
    m_meshes[GROUND_POLYGON] = createMesh("/Ground/Ground.obj");
}

Graphics::Components::Mesh Graphics::Managers::MeshManager::createMesh(const std::string& model_name) noexcept
{
    std::string model_full_path{ Configuration::getModelsPath() };
    model_full_path.append(model_name);
    Tools::ObjParser parser{};
    return parser.parse(model_full_path);
}

Graphics::Components::Mesh& Graphics::Managers::MeshManager::getMesh(EMeshType meshType) noexcept
{
    return m_meshes[meshType];
}

Graphics::Managers::MeshManager::~MeshManager()
{
    for (GLubyte i = 0; i < COUNT_MESH_TYPES; i++)
        m_meshes[i].destroy();
}
