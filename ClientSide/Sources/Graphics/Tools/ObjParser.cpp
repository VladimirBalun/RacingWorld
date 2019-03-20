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
    parseMaterials(currentDirectory, buffer, materialsData);

    Vector<Math::Vector3f> vertices{ 200 };
    Vector<Math::Vector2f> textureCoordinates{ 200 };
    Vector<Math::Vector3f> normals{ 200 };
    Vector<Math::Vector3i> faceElementIndexes{ 400 }; // (0) - vertex, (1) - texture coordinate, (2) - normal

    // indexes start from 1
    vertices.push(Math::Vector3f());
    textureCoordinates.push(Math::Vector2f());
    normals.push(Math::Vector3f());

    char* symbolIterator = const_cast<char*>(buffer.getData());
    while (*symbolIterator != '\0')
    {
        if (strncmp(symbolIterator, "v ", 2) == 0)
        {
            parseVertices(symbolIterator + 2, vertices);
            symbolIterator += 23;
        }
        else if (strncmp(symbolIterator, "vt ", 3) == 0)
        {
            parseTextureCoordinates(symbolIterator + 3, textureCoordinates);
            symbolIterator += 15;
        }
        else if (strncmp(symbolIterator, "vn ", 3) == 0)
        {
            parseNormals(symbolIterator + 3, normals);
            symbolIterator += 23;
        }
        else if (strncmp(symbolIterator, "f ", 2) == 0)
        {
            parseFaceElementIndexes(symbolIterator + 2, faceElementIndexes);
            symbolIterator += 17;
        }
        symbolIterator++;
    }

    return createMesh(vertices, textureCoordinates, normals, faceElementIndexes);
}

void Graphics::Tools::ObjParser::parseMaterials(const String& currentDirectory, const char* buffer, MaterialsData& materialsData) noexcept
{
    char* symbolIterator = const_cast<char*>(buffer);
    while (*symbolIterator != '\r')
    {
        if (strncmp(symbolIterator, "mtlib ", 6) == 0)
        {
            const char* startPosition = symbolIterator + 6;
            const char* endPosition = strchr(startPosition, '\r');
            const GLuint lengthMaterialFileName = (GLuint) (endPosition - startPosition);
            const String materialFileName(startPosition, lengthMaterialFileName, mStringsAllocator);
            const GLuint lengthMaterialFullFileName = strlen(currentDirectory) + lengthMaterialFileName;
            String materialFullFileName(currentDirectory, mStringsAllocator);
            materialFullFileName.append(materialFileName);
            MtlParser::parse(currentDirectory, materialFullFileName, materialsData, mStringsAllocator);
            return;
        }
        symbolIterator++;
    }
}

void Graphics::Tools::ObjParser::parseVertices(char* line, Vector<Math::Vector3f>& vertices) noexcept
{
    static GLfloat xPos = 0.0f;
    static GLfloat yPos = 0.0f;
    static GLfloat zPos = 0.0f;
    sscanf_s(line, "%f %f %f", &xPos, &yPos, &zPos);
    vertices.push({ xPos, yPos, zPos });
}

void Graphics::Tools::ObjParser::parseTextureCoordinates(const char* line, Vector<Math::Vector2f>& textureCoordinates) noexcept
{
    static GLfloat vPos = 0.0f;
    static GLfloat uPos = 0.0f;
    sscanf_s(line, "%f %f", &vPos, &uPos);
    textureCoordinates.push({ vPos, uPos });
}

void Graphics::Tools::ObjParser::parseNormals(const char* line, Vector<Math::Vector3f>& normals) noexcept
{
    static GLfloat xPos = 0.0f;
    static GLfloat yPos = 0.0f;
    static GLfloat zPos = 0.0f;
    sscanf_s(line, "%f %f %f", &xPos, &yPos, &zPos);
    normals.push({ xPos, yPos, zPos });
}

void Graphics::Tools::ObjParser::parseFaceElementIndexes(const char* line, Vector<Math::Vector3i>& faceElementIndexes) noexcept
{
    static GLint vertexIndex[3] = { 0 };
    static GLint normalIndex[3] = { 0 };
    static GLint textureCoordinateIndex[3] = { 0 };
    sscanf_s(line, "%i/%i/%i %i/%i/%i %i/%i/%i", 
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
