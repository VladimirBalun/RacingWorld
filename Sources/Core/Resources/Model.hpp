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
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core { namespace Resources {

    namespace Loaders {

        class OBJLoader;

    }

    class Model : public IResource, public Helpers::Holders::Polymorphic<Model>
    {
        friend class Loaders::OBJLoader;
    public:
        Model() noexcept = default;
        Model(std::vector<glm::vec3>&& vertices, std::vector<glm::vec3>&& normals, std::vector<glm::vec2>&& texture_coordinates) noexcept;
        const std::vector<glm::vec3>& getNormals() const noexcept;
        const std::vector<glm::vec3>& getVertices() const noexcept;
        const std::vector<glm::vec2>& getTextureCoordinates() const noexcept;
        bool load(const std::string& model_path) noexcept override final;
    private:
        std::vector<glm::vec3> m_vertices{};
        std::vector<glm::vec3> m_normals{};
        std::vector<glm::vec2> m_texture_coordinates{};
    };

}}
