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

#include <array>

#include "../OpenGL.hpp"
#include "../Components/Mesh.hpp"
#include "../Tools/ObjParser.hpp"
#include "../../Utils/Configuration.hpp"

namespace Graphics { namespace Managers {

    enum EMeshType 
    {
        CUBE,
        TREE,
        GROUND_POLYGON,
        COUNT_MESH_TYPES // Used for setting size of meshes array 
    };

    class MeshManager
    {
    public:
        GLvoid initializeMeshes() noexcept;
        Components::Mesh& getMesh(EMeshType meshType) noexcept;
        ~MeshManager();
    private:
        Components::Mesh createMesh(const std::string& model_name) noexcept;
    private:
        std::array<Components::Mesh, COUNT_MESH_TYPES> m_meshes;
    };

} }
