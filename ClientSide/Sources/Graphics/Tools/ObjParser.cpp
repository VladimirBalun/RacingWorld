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

#define MAX_COUNT_VERTICES             50
#define MAX_COUNT_TEXTURE_COORDINATES  50
#define MAX_COUNT_NORMALS              50
#define MAX_COUNT_FACE_ELEMENT_INDEXES 100

Graphics::Components::Mesh Graphics::Tools::ObjParser::parse(const char* objFileName, Memory::LinearAllocator& allocator) noexcept
{
    std::uint16_t countVertices = 1;
    std::uint16_t countTextureCoordinates = 1;
    std::uint16_t countNormals = 1;
    std::uint16_t countElementIndexes = 1;

    Math::Vector4f vertices[MAX_COUNT_VERTICES];
    Math::Vector2f textureCoordinates[MAX_COUNT_TEXTURE_COORDINATES];
    Math::Vector3f normals[MAX_COUNT_NORMALS];
    Math::Vector3i faceElementIndexes[MAX_COUNT_FACE_ELEMENT_INDEXES]; // (0) - vertex, (1) - texture coordinate, (2) - normal

    char* buffer = Utils::readFile(objFileName, std::bind(&Memory::LinearAllocator::allocate, 
        &allocator, std::placeholders::_1, std::placeholders::_2));
    char* symbolIterator = buffer;
    while (*symbolIterator != '\0') 
    {
        if (strncmp(symbolIterator, "v ", 2) == 0)
        {
            parseVertices(symbolIterator + 2, vertices + countVertices);
            ASSERT(++countVertices <= MAX_COUNT_VERTICES,
                "Vertices in the file more than size of buffer.");
        }
        else if (strncmp(symbolIterator, "vt ", 3) == 0)
        {
            parseTextureCoordinates(symbolIterator + 3, textureCoordinates + countTextureCoordinates);
            ASSERT(++countTextureCoordinates <= MAX_COUNT_TEXTURE_COORDINATES,
                "Texture coordinates in the file more than size of buffer.");
        }
        else if (strncmp(symbolIterator, "vn ", 3) == 0)
        {
            parseNormals(symbolIterator + 3, normals + countNormals);
            ASSERT(++countNormals <= MAX_COUNT_NORMALS,
                "Normals in the file more than size of buffer.");
        }
        else if (strncmp(symbolIterator, "f ", 2) == 0)
        {
            parseFaceElementIndexes(symbolIterator + 2, faceElementIndexes + countElementIndexes);
            countElementIndexes += 3;
            ASSERT(countElementIndexes <= MAX_COUNT_FACE_ELEMENT_INDEXES,
                "Face element indexes in the file more than size of buffer.");
        }
        symbolIterator++;
    }

    return createMesh(vertices, textureCoordinates, normals, faceElementIndexes, countElementIndexes, allocator);
}

void Graphics::Tools::ObjParser::parseVertices(const char* line, Math::Vector4f* vertices) noexcept
{
    float xPos = 0.0f;
    float yPos = 0.0f;
    float zPos = 0.0f;
    float wPos = 1.0f;
    sscanf_s(line, "%f %f %f %f", &xPos, &yPos, &zPos, &wPos);
    *vertices = { xPos, yPos, zPos, wPos };
}

void Graphics::Tools::ObjParser::parseTextureCoordinates(const char* line, Math::Vector2f* textureCoordinates) noexcept
{
    float vPos = 0.0f;
    float uPos = 0.0f;
    sscanf_s(line, "%f %f", &vPos, &uPos);
    *textureCoordinates = { vPos, uPos };
}

void Graphics::Tools::ObjParser::parseNormals(const char* line, Math::Vector3f* normals) noexcept
{
    float xPos = 0.0f;
    float yPos = 0.0f;
    float zPos = 0.0f;
    sscanf_s(line, "%f %f %f", &xPos, &yPos, &zPos);
    *normals = { xPos, yPos, zPos };
}

void Graphics::Tools::ObjParser::parseFaceElementIndexes(const char* line, Math::Vector3i* faceElementIndexes) noexcept
{
    int vertexIndex[3] = { 0 };
    int normalIndex[3] = { 0 };
    int textureCoordinateIndex[3] = { 0 };
    sscanf_s(line, "%i/%i/%i %i/%i/%i %i/%i/%i", 
        &vertexIndex[0], &normalIndex[0], &textureCoordinateIndex[0],
        &vertexIndex[1], &normalIndex[1], &textureCoordinateIndex[1],
        &vertexIndex[2], &normalIndex[2], &textureCoordinateIndex[2]);
    *(faceElementIndexes) = { vertexIndex[0], normalIndex[0], textureCoordinateIndex[0] };
    *(faceElementIndexes + 1) = { vertexIndex[1], normalIndex[1], textureCoordinateIndex[1] };
    *(faceElementIndexes + 2) = { vertexIndex[2], normalIndex[2], textureCoordinateIndex[2] };
}

Graphics::Components::Mesh Graphics::Tools::ObjParser::createMesh(const Math::Vector4f* vertices, const Math::Vector2f* textureCoordinates,
    const Math::Vector3f* normals, const Math::Vector3i* faceElementIndexes, std::size_t countFaceElementIndexes, Memory::LinearAllocator& allocator) noexcept
{
    std::size_t memorySizeForMeshElements = countFaceElementIndexes * (Graphics::Components::Mesh::SIZE_ELEMENT * sizeof(float));
    float* meshElements = reinterpret_cast<float*>(allocator.allocate(memorySizeForMeshElements));
    for (std::uint16_t i = 1; i < countFaceElementIndexes; i++)
    {
        int vertexIndex = faceElementIndexes[i].getX();
        int normalIndex = faceElementIndexes[i].getY();
        int textureCoordinateIndex = faceElementIndexes[i].getZ();
        vertices[vertexIndex].toArray(&meshElements[i] + Graphics::Components::Mesh::ALIGNMENT_VERTEX + sizeof(float));
        //textureCoordinates[normalIndex].toArray(&meshElements[i] + Graphics::Components::Mesh::ALIGNMENT_TEXTURE_COORDINATE);
        //normals[textureCoordinateIndex].toArray(&meshElements[i] + Graphics::Components::Mesh::ALIGNMENT_NORMAL);
    }
    return Components::Mesh(meshElements, countFaceElementIndexes);
}
