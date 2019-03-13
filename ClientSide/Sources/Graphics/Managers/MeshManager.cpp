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
    mMeshes[CUBE] = createMesh(mMeshesAllocator, "Cube.obj");
    mMeshes[GROUND_POLYGON] = createMesh(mMeshesAllocator, "GroundPolygon.obj");
}

Graphics::Components::Mesh Graphics::Managers::MeshManager::createMesh(Memory::Allocators::LinearAllocator& allocator, const char* modelName) const noexcept
{
    const char* modelsPath = Configuration::getModelsPath();
    char* modelPath = Utils::createStringFromStrings(strlen(modelsPath) + strlen(modelName) + 1,
        std::bind(&Memory::Allocators::LinearAllocator::allocate, &allocator, std::placeholders::_1, std::placeholders::_2), modelsPath, modelName);
    return Tools::ObjParser::parse(modelPath, allocator);
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
