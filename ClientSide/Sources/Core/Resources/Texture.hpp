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
#include <cstdint>

#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core { namespace Resources {

    class Texture : public IResource, public Helpers::Holders::Polymorphic<Texture>
    {
    public:
        Texture() noexcept = default;
        Texture(std::uint16_t width, std::uint16_t height, const unsigned char* data) noexcept
            : m_width(width), m_height(height), m_data(data) {}
        std::uint16_t getWidth() const noexcept;
        std::uint16_t getHeight() const noexcept;
        const unsigned char* getData() const noexcept;
        bool load(const std::string& texture_path) noexcept override final;
    private:
        const unsigned char* m_data = nullptr;
        const std::uint16_t m_width = 0u;
        const std::uint16_t m_height = 0u;
    };

}}
