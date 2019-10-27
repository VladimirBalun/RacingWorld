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

#include "../../Resources/Model.hpp"

namespace Core { namespace Graphics { namespace SceneGraph {

    class Mesh;

    class MeshBuilder
    {
    public:
        static Mesh build(const Resources::Model::Mesh* input_mesh);
    private:
        static unsigned int getCountElements(std::size_t count_vertices) noexcept;
        static unsigned int getCountElements(std::vector<float>& elements) noexcept;
        static void addVec3ToElements(std::vector<float>& elements, const glm::vec3& vector);
        static void addVec2ToElements(std::vector<float>& elements, const glm::vec2& vector);
    private:
        static const std::uint8_t COUNT_ELEMS_IN_POS = 3u;
        static const std::uint8_t COUNT_ELEMS_IN_NORMAL = 3u;
        static const std::uint8_t COUNT_ELEMS_IN_TEXT_COORDINATE = 2u;
        static constexpr std::uint8_t COUNT_ELEMS_IN_VERTEX = COUNT_ELEMS_IN_POS + COUNT_ELEMS_IN_NORMAL + COUNT_ELEMS_IN_TEXT_COORDINATE;
    };

}}}
