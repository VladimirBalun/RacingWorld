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

#include <vector>
#include <unordered_map>
#include <glm/fwd.hpp>

#include "../../Helpers/Macroses.hpp"

namespace Core { namespace Graphics {

    class Mesh;
    class Shader;
    class Material;

}}

namespace Core { namespace Graphics { namespace SceneGraph {

    class Node;

    class Scene
    {
        FWD_DECL_SMART_PTRS_FOR_CLASS(Node)
    private:
        NodeSPtr m_root_node = nullptr;
        std::vector<void*> m_meshes{};
        std::vector<void*> m_materials{};
        std::unordered_map<std::string, Shader> m_shaders{};
    };

}}}
