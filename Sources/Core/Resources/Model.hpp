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

#include <string>
#include <vector>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core { namespace Resources {

    class Model final : public IResource, public Helpers::Holders::Polymorphic<Model>
    {
    public:

        struct Vertex
        {
        public:
            Vertex() noexcept = default;
            Vertex(glm::vec3&& normal, glm::vec3&& position, glm::vec2&& texture_coordinate) noexcept
                : m_normal(normal), m_position(position), m_texture_coordinate(texture_coordinate) {}
            const glm::vec3& getNormal() const noexcept;
            const glm::vec3& getPosition() const noexcept;
            const glm::vec2& getTextureCoordinate() const noexcept;
        private:
            glm::vec3 m_normal{};
            glm::vec3 m_position{};
            glm::vec2 m_texture_coordinate{};
        };

        class Mesh
        {
        public:
            Mesh() noexcept = default;
            Mesh(std::size_t count_vertices, std::size_t count_indices) noexcept;
            template<typename... Args>
            void emplaceVertex(Args... args);
            void addIndex(unsigned int index);
            void setMaterialName(const std::string& name) noexcept;
            const std::string getMaterialName() const noexcept;
            const std::vector<Vertex>& getVertices() const noexcept;
            const std::vector<unsigned int>& getIndices() const noexcept;
        private:
            std::string m_material_name{};
            std::vector<Vertex> m_vertices{};
            std::vector<unsigned int> m_indices{};
        };

    private:
        using meshes_t = std::unordered_map<std::string, Mesh>;
    public:
        Model() noexcept = default;
        explicit Model(std::size_t count_meshes) noexcept;
        void addMesh(const std::string& name, Mesh&& mesh);
        bool isExistMeshByName(const std::string& name) const noexcept;
        const Mesh* getMeshByName(const std::string& name) const noexcept;
        meshes_t::const_iterator meshesBegin() const noexcept;
        meshes_t::const_iterator meshesEnd() const noexcept;
    public:
        bool load(const std::string& model_path) noexcept override;
    private:
        meshes_t m_meshes{};
    };

    template<typename... Args>
    void Model::Mesh::emplaceVertex(Args... args)
    {
        m_vertices.emplace_back(std::forward<Args>(args)...);
    }

}}
