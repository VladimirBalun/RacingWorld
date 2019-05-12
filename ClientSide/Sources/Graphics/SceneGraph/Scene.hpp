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

#include "Node.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "SceneGraphBuilder.hpp"
#include "../OpenGL.hpp"
#include "../Managers/MeshManager.hpp"
#include "../Managers/ShaderManager.hpp"
#include "../../Utils/Time.hpp"
#include "../../WindowSystem/WindowEventListener.hpp"

namespace Graphics { namespace SceneGraph {

    class Scene
    {
    public:
        explicit Scene(HDC& window_context) noexcept;
        GLvoid render() noexcept;
        GLvoid update() noexcept;
    private:
        GLvoid renderNode(std::shared_ptr<Node>& node, Tools::ShaderProgram& shader) noexcept;
    private:
        std::shared_ptr<Node> m_root_node{};
        HDC& m_window_context;
        Light m_scene_light;
        Camera m_scene_camera;
        Managers::MeshManager m_mesh_manager;
        Managers::ShaderManager m_shader_manager;
    };

} }
