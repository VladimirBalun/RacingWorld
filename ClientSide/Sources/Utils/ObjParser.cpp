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
    std::vector<Math::Vector4<float>> vertices;
    std::vector<Math::Vector3<float>> normals;
    std::vector<Math::Vector2<float>> textureCoordinates;
    std::vector<std::tuple<int, int, int>> indexes; // (0) - vertex, (1) - texture, (2) - normal 
    
    // TODO: will nead optimize work with reallocation of strings
    std::string line;
    std::ifstream inputStream(objFileName);
    while (std::getline(inputStream, line))
    {
        if (line.substr(0, 2) == "v ")
            addVertex(vertices, line.substr(2));
        if (line.substr(0, 3) == "vn ")
            addNormal(normals, line.substr(3));
        if (line.substr(0, 3) == "vt ")
            addTextureCoordinate(textureCoordinates, line.substr(3));
        if (line.substr(0, 2) == "f ")
            addIndex(indexes, line.substr(2));
    }

    return Graphics::Components::Mesh(
        std::move(normals),
        std::move(vertices),
        std::move(textureCoordinates),
        std::move(indexes)
    );
}

void Utils::ObjParser::addVertex(std::vector<Math::Vector4<float>>& vertices, const std::string& line)
{
    std::istringstream stream(line);
    float x, y, z;
    stream >> x;
    stream >> y;
    stream >> z;
    vertices.push_back({ x, y, z, 1.0f });
}

void Utils::ObjParser::addNormal(std::vector<Math::Vector3<float>>& normals, const std::string& line)
{
    std::istringstream stream(line);
    float x, y, z;
    stream >> x;
    stream >> y;
    stream >> z;
    normals.push_back({ x, y, z });
}

void Utils::ObjParser::addTextureCoordinate(std::vector<Math::Vector2<float>>& textureCoordinates, const std::string& line)
{
    std::istringstream stream(line);
    float u, v;
    stream >> u;
    stream >> v;
    textureCoordinates.push_back({ u, v });
}

void Utils::ObjParser::addIndex(std::vector<std::tuple<int, int, int>>& indexes, const std::string& line)
{
    // TODO: Need to add getting indexes
}
