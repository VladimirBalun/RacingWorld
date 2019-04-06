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

Graphics::Components::Mesh Graphics::Tools::ObjParser::parse(const char* objFileName) noexcept
{
    const String buffer(Utils::readFile(objFileName, mStringsAllocator), mStringsAllocator);
    if (!buffer)
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Model was not read.");
    }

    MaterialsData materialsData;
    const String currentDirectory(Utils::getPathWithoutFilename(objFileName, mStringsAllocator), mStringsAllocator);

    Vector<Math::Vector3f> vertices{ 200 };
    Vector<Math::Vector2f> textureCoordinates{ 200 };
    Vector<Math::Vector3f> normals{ 200 };
    Vector<Math::Vector3i> faceElementIndexes{ 400 }; // (0) - vertex, (1) - texture coordinate, (2) - normal

    // indexes start from 1
    vertices.push(Math::Vector3f());
    textureCoordinates.push(Math::Vector2f());
    normals.push(Math::Vector3f());

    char* iterator = const_cast<char*>(buffer.getData());
    while (*iterator != '\0')
    {
        if (strncmp(iterator, "v ", 2) == 0)
        {
            parseVertices(iterator + 2, vertices);
            iterator += 23;
        }
        else if (strncmp(iterator, "vt ", 3) == 0)
        {
            parseTextureCoordinates(iterator + 3, textureCoordinates);
            iterator += 15;
        }
        else if (strncmp(iterator, "vn ", 3) == 0)
        {
            parseNormals(iterator + 3, normals);
            iterator += 23;
        }
        else if (strncmp(iterator, "f ", 2) == 0)
        {
            parseFaceElementIndexes(iterator + 2, faceElementIndexes);
            iterator += 17;
        }
        else if (strncmp(iterator, "mtlib ", 6) == 0)
        {
            parseMaterials(iterator + 6, currentDirectory, materialsData);
        }
        iterator++;
    }

    return createMesh(vertices, textureCoordinates, normals, faceElementIndexes);
}

void Graphics::Tools::ObjParser::parseMaterials(char* iterator, const String& currentDirectory, MaterialsData& materialsData) noexcept
{
    std::size_t materialFileNameLength = 0;
    const char* tmpIterator = iterator;
    while ( (*tmpIterator != ' ') && (*tmpIterator != '\r') &&  (*tmpIterator != '\n') )
    {
        tmpIterator++;
        materialFileNameLength++;
    }
    const String materialFileName(iterator, materialFileNameLength, mStringsAllocator);
    const GLuint lengthMaterialFullFileName = strlen(currentDirectory) + materialFileNameLength;
    String materialFullFileName(currentDirectory, mStringsAllocator);
    materialFullFileName.append(materialFileName);
    MtlParser::parse(currentDirectory, materialFullFileName, materialsData, mStringsAllocator);
    return;
}

void Graphics::Tools::ObjParser::parseVertices(char* iterator, Vector<Math::Vector3f>& vertices) noexcept
{
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
    GLfloat zPos = 0.0f;
    sscanf_s(iterator, "%f %f %f", &xPos, &yPos, &zPos);
    vertices.push({ xPos, yPos, zPos });
}

void Graphics::Tools::ObjParser::parseTextureCoordinates(const char* iterator, Vector<Math::Vector2f>& textureCoordinates) noexcept
{
    GLfloat vPos = 0.0f;
    GLfloat uPos = 0.0f;
    sscanf_s(iterator, "%f %f", &vPos, &uPos);
    textureCoordinates.push({ vPos, uPos });
}

void Graphics::Tools::ObjParser::parseNormals(const char* iterator, Vector<Math::Vector3f>& normals) noexcept
{
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
    GLfloat zPos = 0.0f;
    sscanf_s(iterator, "%f %f %f", &xPos, &yPos, &zPos);
    normals.push({ xPos, yPos, zPos });
}

void Graphics::Tools::ObjParser::parseFaceElementIndexes(const char* iterator, Vector<Math::Vector3i>& faceElementIndexes) noexcept
{
    GLint vertexIndex[3] = { 0 };
    GLint normalIndex[3] = { 0 };
    GLint textureCoordinateIndex[3] = { 0 };
    sscanf_s(iterator, "%i/%i/%i %i/%i/%i %i/%i/%i",
        &vertexIndex[0], &textureCoordinateIndex[0], &normalIndex[0],
        &vertexIndex[1], &textureCoordinateIndex[1], &normalIndex[1],
        &vertexIndex[2], &textureCoordinateIndex[2], &normalIndex[2]);
    faceElementIndexes.push({ vertexIndex[0], textureCoordinateIndex[0], normalIndex[0] });
    faceElementIndexes.push({ vertexIndex[1], textureCoordinateIndex[1], normalIndex[1] });
    faceElementIndexes.push({ vertexIndex[2], textureCoordinateIndex[2], normalIndex[2] });
}

Graphics::Components::Mesh Graphics::Tools::ObjParser::createMesh(const Vector<Math::Vector3f>& vertices, const Vector<Math::Vector2f>& textureCoordinates,
    const Vector<Math::Vector3f>& normals, const Vector<Math::Vector3i>& faceElementIndexes) noexcept
{
    const GLuint memorySizeForMeshElements = faceElementIndexes.getSize() * (Components::Mesh::SIZE_ELEMENT * sizeof(GLfloat));
    GLfloat* meshElements = reinterpret_cast<GLfloat*>(mMeshAllocator.allocate(memorySizeForMeshElements));
    GLuint innerAlignmentForElements = 0;
    for (GLuint i = 0; i < faceElementIndexes.getSize(); i++)
    {
        int vertexIndex = faceElementIndexes.at(i).getX();
        int normalIndex = faceElementIndexes.at(i).getY();
        int textureCoordinateIndex = faceElementIndexes.at(i).getZ();
        vertices[vertexIndex].toArray(meshElements + innerAlignmentForElements + Components::Mesh::ALIGNMENT_VERTEX);
        textureCoordinates[normalIndex].toArray(meshElements + innerAlignmentForElements + Components::Mesh::ALIGNMENT_TEXTURE_COORDINATE);
        normals[textureCoordinateIndex].toArray(meshElements + innerAlignmentForElements + Components::Mesh::ALIGNMENT_NORMAL);
        innerAlignmentForElements += Components::Mesh::SIZE_ELEMENT;
    }

    return Components::Mesh(meshElements, faceElementIndexes.getSize());
}
