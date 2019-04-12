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

#include <iostream>

#define SPACE_LENGTH                   1 // _
#define LETTER_LENGTH                  1 // ?
#define MATERIAL_LIB_WORD_LENGTH       5 // mtlib
#define VERTEX_WORD_LENGTH             1 // v
#define NORMAL_WORD_LENGTH             2 // vn
#define TEXTURE_COORDINATE_WORD_LENGTH 2 // vt
#define FRAGMENT_WORD_LENGHT           1 // f

#define MIN_NUMBER_LENGTH             6 // 0.0000
#define MIN_FRAGMENT_LENGTH           5 // 0/0/0
#define MIN_FILE_EXTENSION_LENGTH     LETTER_LENGTH + (LETTER_LENGTH * 3) // .???
#define MIN_MATERIAL_LIB_LENGTH       LETTER_LENGTH + MIN_FILE_EXTENSION_LENGTH // ?.???
#define MIN_2D_VECTOR_LENGTH          MIN_NUMBER_LENGTH + SPACE_LENGTH + MIN_NUMBER_LENGTH // 0.0000 0.0000
#define MIN_3D_VECTOR_LENGTH          MIN_NUMBER_LENGTH + SPACE_LENGTH + MIN_NUMBER_LENGTH + SPACE_LENGTH + MIN_NUMBER_LENGTH // 0.0000 0.0000 0.0000
#define MIN_TRIANGULAR_POLYGON_LENGTH MIN_FRAGMENT_LENGTH + SPACE_LENGTH + MIN_FRAGMENT_LENGTH + SPACE_LENGTH + MIN_FRAGMENT_LENGTH // 0/0/0 0/0/0 0/0/0

struct ObjSizeParameter
{
    GLuint countVertices = 0;
    GLuint countNormals = 0;
    GLuint countTextureCoordinates = 0;
    GLuint countFragments = 0;
};

static ObjSizeParameter getObjSizeParameters(char* objFileData) noexcept;

Graphics::Components::Mesh Graphics::Tools::ObjParser::parse(const String& objFileName) noexcept
{
    char* buffer = Utils::readFile(objFileName.getData(), mStringsAllocator);
    if (!buffer)
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Model was not read.");
    }

    MaterialsData materialsData;
    ObjSizeParameter objSizeParameter = getObjSizeParameters(buffer);
    const String currentDirectory(getPathWithoutFilename(objFileName));

    Vector<Math::Vector3f> vertices(objSizeParameter.countVertices);
    Vector<Math::Vector2f> textureCoordinates(objSizeParameter.countTextureCoordinates);
    Vector<Math::Vector3f> normals(objSizeParameter.countNormals);
    Vector<Math::Vector3i> faceElementIndexes(objSizeParameter.countFragments * 3); // (0) - vertex, (1) - texture coordinate, (2) - normal

    // indexes start from 1
    vertices.push(Math::Vector3f());
    textureCoordinates.push(Math::Vector2f());
    normals.push(Math::Vector3f());

    char* iterator = buffer;
    while (*iterator != '\0')
    {
        if (strncmp(iterator, "v ", VERTEX_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += VERTEX_WORD_LENGTH + SPACE_LENGTH;
            parseVertices(iterator, vertices);
            iterator += MIN_3D_VECTOR_LENGTH + SPACE_LENGTH;
        }
        else if (strncmp(iterator, "vt ", TEXTURE_COORDINATE_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += TEXTURE_COORDINATE_WORD_LENGTH + SPACE_LENGTH;
            parseTextureCoordinates(iterator, textureCoordinates);
            iterator += MIN_2D_VECTOR_LENGTH + SPACE_LENGTH;
        }
        else if (strncmp(iterator, "vn ", NORMAL_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += NORMAL_WORD_LENGTH + SPACE_LENGTH;
            parseNormals(iterator, normals);
            iterator += MIN_3D_VECTOR_LENGTH + SPACE_LENGTH;
        }
        else if (strncmp(iterator, "f ", FRAGMENT_WORD_LENGHT + SPACE_LENGTH) == 0)
        {
            iterator += FRAGMENT_WORD_LENGHT + SPACE_LENGTH;
            parseFaceElementIndexes(iterator, faceElementIndexes);
            iterator += MIN_TRIANGULAR_POLYGON_LENGTH + SPACE_LENGTH;
        }
        else if (strncmp(iterator, "mtlib ", MATERIAL_LIB_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += MATERIAL_LIB_WORD_LENGTH + SPACE_LENGTH;
            parseMaterials(iterator, currentDirectory, materialsData);
            iterator += MIN_MATERIAL_LIB_LENGTH;
        }
        iterator++;
    }

    return createMesh(vertices, textureCoordinates, normals, faceElementIndexes);
}

ObjSizeParameter getObjSizeParameters(char* objFileData) noexcept
{
    ObjSizeParameter objSizeParameter;
    char* iterator = objFileData;
    while ( (*iterator != '\0') && (*iterator != '\n') )
    {
        if (strncmp(iterator, "#vc ", 4) == 0)
            sscanf_s(iterator + 4, "%u", &objSizeParameter.countVertices);
        if (strncmp(iterator, "#vnc ", 5) == 0)
            sscanf_s(iterator + 5, "%u", &objSizeParameter.countNormals);
        if (strncmp(iterator, "#vtc ", 5) == 0)
            sscanf_s(iterator + 5, "%u", &objSizeParameter.countTextureCoordinates);
        if (strncmp(iterator, "#fc ", 4) == 0)
            sscanf_s(iterator + 4, "%u", &objSizeParameter.countFragments);
        iterator++;
    }
    return objSizeParameter;
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
    const String materialFileName(iterator, materialFileNameLength);
    const GLuint lengthMaterialFullFileName = static_cast<GLuint>(currentDirectory.getLength() + materialFileNameLength);
    String materialFullFileName(currentDirectory);
    materialFullFileName.append(materialFileName.getData());
    MtlParser mtlParser(currentDirectory, materialFullFileName);
    mtlParser.parse(materialsData);
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
    const GLuint memorySizeForMeshElements = static_cast<GLuint>(faceElementIndexes.getSize() * (Components::Mesh::SIZE_ELEMENT * sizeof(GLfloat)));
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

    return Components::Mesh(meshElements, static_cast<GLuint>(faceElementIndexes.getSize()));
}
