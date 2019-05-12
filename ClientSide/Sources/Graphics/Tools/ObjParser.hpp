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

#include <array>
#include <vector>
#include <string>

#include "../Components/Mesh.hpp"
#include "../Components/Material.hpp"
#include "../../Utils/FileSystem.hpp"
#include "../../EventSystem/EventManager.hpp"

namespace Graphics { namespace Tools {

    class ObjParser 
    {
    public:
        Components::Mesh parse(const std::string_view& obj_filename) noexcept;
    private:
        GLvoid parseVertices(const char* iterator, std::vector<Math::Vector3f>& vertices) noexcept;
        GLvoid parseTextureCoordinates(const char* iterator, std::vector<Math::Vector2f>& texture_coordinates) noexcept;
        GLvoid parseNormals(const char* iterator, std::vector<Math::Vector3f>& normals) noexcept;
        GLvoid parseFaceElementIndexes(const char* iterator, std::vector<Math::Vector3i>& face_element_indexes) noexcept;
    };

} }
