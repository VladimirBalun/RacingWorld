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
#include <fstream>
#include <algorithm>

#include "FileSystem.hpp"
#include "../Graphics/Components/Mesh.hpp"

namespace Utils {

    class ObjParser 
    {
    public:
        static Graphics::Components::Mesh parse(const char* objFileName);
    private:
        static void addVertex(std::vector<Math::Vector4<float>>& vertices, const std::string_view& line);
        static void addNormal(std::vector<Math::Vector3<float>>& normals, const std::string_view& line);
        static void addTextureCoordinate(std::vector<Math::Vector2<float>>& textureCoordinates, const std::string_view& line);
        static void addIndex(std::vector<std::tuple<int, int, int>>& indexes, const std::string_view& line);
    };

}