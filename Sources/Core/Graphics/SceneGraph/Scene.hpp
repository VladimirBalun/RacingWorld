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
#include <optional>
#include <unordered_map>

#include "Node.hpp"

namespace Core { namespace Graphics {

    class Mesh;
    class Shader;
    class Material;

    // TODO:
    class Material {};
    class Mesh {};

}}

namespace Core { namespace Graphics { namespace SceneGraph {

    class Scene
    {
    public:
        void addMesh(Mesh&& mesh);
        void addMaterial(Material&& material);
        void addShader(const std::string& shader_id, Shader&& shader);
        template<typename... Args>
        void emplaceMesh(Args... args);
        template<typename... Args>
        void emplaceMaterial(Args... args);
        template<typename... Args>
        void emplaceShader(const std::string& shader_id, Args... args);
        void setRootNode(NodeSPtr root_node) noexcept;
        NodeSPtr getRootNode() const noexcept;
        const Shader* getShaderByID(const std::string& shader_id) const noexcept;
    private:
        NodeSPtr m_root_node = nullptr;
        std::vector<Mesh> m_meshes{};
        std::vector<Material> m_materials{};
        std::unordered_map<std::string, Shader> m_shaders{};
    };

    template<typename... Args>
    void Scene::emplaceMesh(Args... args)
    {
        m_meshes.emplace_back(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Scene::emplaceMaterial(Args... args)
    {
        m_materials.emplace_back(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Scene::emplaceShader(const std::string& shader_id, Args... args)
    {
        m_shaders.emplace(shader_id, std::forward<Args>(args)...);
    }

}}}
