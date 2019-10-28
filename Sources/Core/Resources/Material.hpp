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

#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core { namespace Resources {

    class Material final : public IResource, public Helpers::Holders::Polymorphic<Material>
    {
    public:
        void setShininess(float shininess) noexcept;
        void setAmbientTextureName(std::string&& texture_name) noexcept;
        void setDiffuseTextureName(std::string&& texture_name) noexcept;
        void setSpecularTextureName(std::string&& texture_name) noexcept;
        float getShininess() const noexcept;
        const std::string& getAmbientTextureName() const noexcept;
        const std::string& getDiffuseTextureName() const noexcept;
        const std::string& getSpecularTextureName() const noexcept;
    private:
        bool load(const std::string& material_path) noexcept override;
    private:
        float m_shininess = 0.0f;
        std::string m_ambient_texture_name{};
        std::string m_diffuse_texture_name{};
        std::string m_specular_texture_name{};
    };

}}
