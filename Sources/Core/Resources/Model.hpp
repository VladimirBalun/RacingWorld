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

    class Model : public IResource, public Helpers::Holders::Polymorphic<Model>
    {
        using children_models_t = std::unordered_map<std::string, Model>;
    public:
        struct Vertex
        {
            glm::vec3 normal{};
            glm::vec3 position{};
            glm::vec2 texture_coordinate{};
        };
    public:
        Model() noexcept = default;
        Model(std::size_t count_vertices, std::size_t count_indices) noexcept;
        template<typename... Args>
        void emplaceVertex(Args... args);
        void addIndex(unsigned int index);
        void addChild(const std::string& name, Model&& child);
        void setMaterialName(const std::string& name) noexcept;
        const std::string getMaterialName() const noexcept;
        const std::vector<Vertex>& getVertices() const noexcept;
        const std::vector<unsigned int>& getIndices() const noexcept;
        bool isExistChildByName(const std::string& name) const noexcept;
        const Model* getChildByName(const std::string& name) const noexcept;
        children_models_t::const_iterator childrenBegin() const noexcept;
        children_models_t::const_iterator childrenEnd() const noexcept;
    public:
        bool load(const std::string& model_path) noexcept override;
    private:
        std::string m_material_name{};
        std::vector<Vertex> m_vertices{};
        std::vector<unsigned int> m_indices{};
        children_models_t m_children{};
    };

    template<typename... Args>
    void Model::emplaceVertex(Args... args)
    {
        m_vertices.emplace_back(std::forward<Args>(args)...);
    }

}}
