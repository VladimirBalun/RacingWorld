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

#include "IResource.hpp"

namespace Core { namespace Resources { namespace Loaders {

    class OBJLoader;

}}}

namespace Core { namespace Resources {

    FWD_DECLARE_SMART_PTRS_FOR_CLASS(Model)

    class Model : public IResource
    {
        friend class Loaders::OBJLoader;
    public:
        Model() noexcept = default;
        Model(std::vector<void*>&& vertices, std::vector<void*>&& normals, std::vector<void*>&& texture_coordinates) noexcept;
        const std::vector<void*>& getNormals() const noexcept;
        const std::vector<void*>& getVertices() const noexcept;
        const std::vector<void*>& getTextureCoordinates() const noexcept;
        bool load(const std::string& model_path) noexcept override final;
    private:
        const std::vector<void*> m_vertices{};
        const std::vector<void*> m_normals{};
        const std::vector<void*> m_texture_coordinates{};
    };

}}
