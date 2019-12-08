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

#include <stack>
#include <glm/mat4x4.hpp>

#include "Camera.hpp"
#include "../Helpers/Macroses.hpp"

namespace Core::Graphics 
{

    namespace SceneGraph
    {

        class Node;
        class Scene;

        DECL_SMART_PTRS(Node)

    }

    class Shader;

    class Renderer
    {
    public:
        void draw(const SceneGraph::Scene& scene, const std::string& shader_id);
    private:
        void drawNode(SceneGraph::NodeSPtr node);
        void updateCamera() noexcept;
    private:
        Camera m_camera;
        const Shader* m_basic_shader = nullptr;
        std::stack<glm::mat4x4> m_transformations_stack;
    };

}
