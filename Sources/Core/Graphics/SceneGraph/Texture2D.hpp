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

namespace Core::Graphics::SceneGraph
{

    class Texture2D
    {
    public:
        Texture2D() noexcept = default;
        Texture2D(std::uint16_t width, std::uint16_t height, const unsigned char* data) noexcept;
        void bind() const noexcept;
        void unbind() const noexcept;
        void free() noexcept;
    private:
        void generateTextureIdentifier() noexcept;
        void setTextureParameters() const noexcept;
        void fillTextureData(std::uint16_t width, std::uint16_t height, const unsigned char* data) const noexcept;
    private:
        unsigned int m_texture_id = 0u;
    };

}
