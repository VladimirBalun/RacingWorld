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

#include <unordered_map>

namespace Core::Graphics
{

    class Shader;

    namespace SceneGraph
    {

        class Mesh;
        class Node;

        class Scene
        {
        public:
            void addMesh(const std::string& shader_id, Mesh&& mesh);
            void addShader(const std::string& shader_id, Shader&& shader);
            void setRootNode(std::shared_ptr<Node> root_node) noexcept;
            std::shared_ptr<Node> getRootNode() const noexcept;
            bool isExistsMesh(const std::string& mesh_id) const noexcept;
            const Mesh* getMeshByID(const std::string& mesh_id) const noexcept;
            const Shader* getShaderByID(const std::string& shader_id) const noexcept;
            ~Scene();
        private:
            std::shared_ptr<Node> m_root_node = nullptr;
            std::unordered_map<std::string, Mesh> m_meshes{};
            std::unordered_map<std::string, Shader> m_shaders{};
        };

    }

}
