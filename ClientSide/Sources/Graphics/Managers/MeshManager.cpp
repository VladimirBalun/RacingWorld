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
    mMeshes[TREE] = createMesh("Tree/Tree.obj");
    mMeshes[CUBE] = createMesh("Cube.obj");
    mMeshes[GROUND_POLYGON] = createMesh("GroundPolygon.obj");
}

Graphics::Components::Mesh Graphics::Managers::MeshManager::createMesh(const char* modelName) noexcept
{
    const char* modelsPath = Configuration::getModelsPath();
    char* modelPath = Utils::createStringFromStrings(strlen(modelsPath) + strlen(modelName) + 1,
        std::bind(&Memory::Allocators::LinearAllocator::allocate, &mMeshesAllocator, std::placeholders::_1), modelsPath, modelName);
    Tools::ObjParser objParser(mMeshesAllocator);
    return objParser.parse(modelPath);
}

Graphics::Components::Mesh& Graphics::Managers::MeshManager::getMesh(EMeshType meshType) noexcept
{
    return mMeshes[meshType];
}

Graphics::Managers::MeshManager::~MeshManager()
{
    for (std::uint8_t i = 0; i < COUNT_MESH_TYPES; i++)
        mMeshes[i].destroy();
}
