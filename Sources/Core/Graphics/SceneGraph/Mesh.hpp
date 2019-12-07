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

#include "Texture2D.hpp"
#include "../../Resources/Model.hpp"
#include "../../Helpers/Macroses.hpp"

namespace Core::Resources
{

    FWD_DECL_SMART_PTRS_FOR_CLASS(Image);

}

namespace Core::Graphics::SceneGraph 
{

    class Mesh
    {
    public:
        Mesh() noexcept = default;
        Mesh(Texture2D texture, std::vector<float>&& elements, unsigned int count_elements) noexcept;
        void draw() const noexcept;
        ~Mesh();
    private:
        void generateIdentifiers();
        void bindDataIdentifiers();
        void unbindDataIdentifiers();
        void fillBuffersData();
    private:
        std::vector<float> m_elements{};
        Texture2D m_texture;
        unsigned int m_vbo = 0u;
        unsigned int m_vao = 0u;
        unsigned int m_count_elements = 0u;
    };

}
