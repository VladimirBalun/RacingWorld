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

#include "../OpenGL.hpp"
#include "../Components/Mesh.hpp"
#include "../Tools/ObjParser.hpp"
#include "../../Utils/Configuration.hpp"
#include "../../Memory/Allocators/LinearAllocator.hpp"

namespace Graphics { namespace Managers {

    enum EMeshType 
    {
        CUBE,
        COUNT_MESH_TYPES // Used for setting size of meshes array 
    };

    class MeshManager : Memory::INonCopyable
    {
    public:
        explicit MeshManager()
            : mMeshesAllocator(ONE_VIRTUAL_PAGE) {}
        GLvoid initializeMeshes() noexcept;
        Components::Mesh& getMesh(EMeshType meshType) noexcept;
        ~MeshManager();
    private:
        Components::Mesh createMesh(Memory::Allocators::LinearAllocator& allocator, const char* modelPath) const noexcept;
    private:
        bool mIsInitialized = false;
        Components::Mesh mMeshes[COUNT_MESH_TYPES];
        Memory::Allocators::LinearAllocator mMeshesAllocator;
    };

} }
