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

#include <cstdint>

#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core::Resources 
{

    class Image final : public IResource, public Helpers::Holders::Polymorphic<Image>
    {
    public:
        void setWidth(std::uint16_t width) noexcept;
        void setHeight(std::uint16_t height) noexcept;
        void setData(unsigned char* data) noexcept;
        std::uint16_t getWidth() const noexcept;
        std::uint16_t getHeight() const noexcept;
        const unsigned char* getData() const noexcept;
        bool load(std::string_view image_path) noexcept override;
        ~Image();
    private:
        unsigned char* m_data = nullptr;
        std::uint16_t m_width = 0u;
        std::uint16_t m_height = 0u;
    };

}
