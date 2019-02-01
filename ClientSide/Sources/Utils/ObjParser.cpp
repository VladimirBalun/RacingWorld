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

#include "ObjParser.hpp"

Graphics::Components::Mesh Utils::ObjParser::parse(const char* objFileName)
{
    // TODO: need to change vectors on custom containers
    std::vector<Math::Vector4<float>> vertices;
    std::vector<Math::Vector3<float>> normals;
    std::vector<Math::Vector2<float>> textureCoordinates;
    std::vector<Graphics::Components::MeshIndex> indexes; // (0) - vertex, (1) - texture, (2) - normal 

    std::string line;
    std::ifstream inputStream(objFileName);
    while (std::getline(inputStream, line))
    {
        if (std::string_view(line).substr(0, 2) == "v ")
            addVertex(vertices, std::string_view(line));
        if (std::string_view(line).substr(0, 3) == "vn ")
            addNormal(normals, std::string_view(line));
        if (std::string_view(line).substr(0, 3) == "vt ")
            addTextureCoordinate(textureCoordinates, std::string_view(line).substr(3));
        if (std::string_view(line).substr(0, 2) == "f ")
            addIndex(indexes, std::string_view(line));
    }

    return Graphics::Components::Mesh(
        std::move(normals),
        std::move(vertices),
        std::move(textureCoordinates),
        std::move(indexes)
    );
}

void Utils::ObjParser::addVertex(std::vector<Math::Vector4<float>>& vertices, const std::string_view& line)
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    sscanf(line.data(), "v %f %f %f", x, y, z);
    vertices.emplace_back(x, y, z, 1.0f);
}

void Utils::ObjParser::addNormal(std::vector<Math::Vector3<float>>& normals, const std::string_view& line)
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    sscanf(line.data(), "vn %f %f %f", x, y, z);
    normals.emplace_back(x, y, z);
}

void Utils::ObjParser::addTextureCoordinate(std::vector<Math::Vector2<float>>& textureCoordinates, const std::string_view& line)
{
    float u = 0.0f;
    float v = 0.0f;
    sscanf(line.data(), "vt %f %f", u, v);
    textureCoordinates.emplace_back(u, v);
}

void Utils::ObjParser::addIndex(std::vector<Graphics::Components::MeshIndex>& indexes, const std::string_view& line)
{
    // TODO: Need to add getting indexes
}
