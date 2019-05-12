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

struct ObjFileSizeParameter
{
    GLuint count_vertices = 0;
    GLuint count_normals = 0;
    GLuint count_texture_coordinates = 0;
    GLuint count_fragments = 0;
};

static ObjFileSizeParameter getObjSizeParameters(const std::vector<char>& obj_file_data) noexcept;

Graphics::Components::Mesh Graphics::Tools::ObjParser::parse(const std::string_view& objFileName) noexcept
{
    std::vector<char> buffer = Utils::readFile(std::string(objFileName));
    if (buffer.empty())
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Model was not read.");
    }

    ObjFileSizeParameter obj_file_size_parameter = getObjSizeParameters(buffer);

    std::vector<Math::Vector3f> vertices(1);
    vertices.reserve(obj_file_size_parameter.count_vertices + 1);
    std::vector<Math::Vector2f> texture_coordinates(1);
    texture_coordinates.reserve(obj_file_size_parameter.count_texture_coordinates + 1);
    std::vector<Math::Vector3f> normals(1);
    normals.reserve(obj_file_size_parameter.count_normals + 1);
    std::vector<Math::Vector3i> face_element_indexes{}; // (0) - vertex, (1) - texture coordinate, (2) - normal
    face_element_indexes.reserve(obj_file_size_parameter.count_fragments * 3);

    const char* iterator = buffer.data();
    while (*iterator != '\0')
    {
        if (strncmp(iterator, "v ", VERTEX_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += VERTEX_WORD_LENGTH + SPACE_LENGTH;
            parseVertices(iterator, vertices);
            iterator += MIN_3D_VECTOR_LENGTH;
        }
        else if (strncmp(iterator, "vt ", TEXTURE_COORDINATE_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += TEXTURE_COORDINATE_WORD_LENGTH + SPACE_LENGTH;
            parseTextureCoordinates(iterator, texture_coordinates);
            iterator += MIN_2D_VECTOR_LENGTH;
        }
        else if (strncmp(iterator, "vn ", NORMAL_WORD_LENGTH + SPACE_LENGTH) == 0)
        {
            iterator += NORMAL_WORD_LENGTH + SPACE_LENGTH;
            parseNormals(iterator, normals);
            iterator += MIN_3D_VECTOR_LENGTH;
        }
        else if (strncmp(iterator, "f ", FRAGMENT_WORD_LENGHT + SPACE_LENGTH) == 0)
        {
            iterator += FRAGMENT_WORD_LENGHT + SPACE_LENGTH;
            parseFaceElementIndexes(iterator, face_element_indexes);
            iterator += MIN_TRIANGULAR_POLYGON_LENGTH;
        }
        iterator++;
    }

    return Components::Mesh(std::move(vertices), std::move(texture_coordinates), std::move(normals), std::move(face_element_indexes));
}

ObjFileSizeParameter getObjSizeParameters(const std::vector<char>& obj_file_data) noexcept
{
    ObjFileSizeParameter obj_file_size_parameter{};
    const char* iterator = obj_file_data.data();
    while ( (*iterator != '\0') && (*iterator != '\n') )
    {
        if (strncmp(iterator, "#vc ", 4) == 0)
            sscanf_s(iterator + 4, "%u", &obj_file_size_parameter.count_vertices);
        if (strncmp(iterator, "#vnc ", 5) == 0)
            sscanf_s(iterator + 5, "%u", &obj_file_size_parameter.count_normals);
        if (strncmp(iterator, "#vtc ", 5) == 0)
            sscanf_s(iterator + 5, "%u", &obj_file_size_parameter.count_texture_coordinates);
        if (strncmp(iterator, "#fc ", 4) == 0)
            sscanf_s(iterator + 4, "%u", &obj_file_size_parameter.count_fragments);
        iterator++;
    }
    return obj_file_size_parameter;
}

GLvoid Graphics::Tools::ObjParser::parseVertices(const char* iterator, std::vector<Math::Vector3f>& vertices) noexcept
{
    GLfloat x_pos = 0.0f;
    GLfloat y_pos = 0.0f;
    GLfloat z_pos = 0.0f;
    sscanf_s(iterator, "%f %f %f", &x_pos, &y_pos, &z_pos);
    vertices.emplace_back(x_pos, y_pos, z_pos);
}

GLvoid Graphics::Tools::ObjParser::parseTextureCoordinates(const char* iterator, std::vector<Math::Vector2f>& texture_coordinates) noexcept
{
    GLfloat v_pos = 0.0f;
    GLfloat u_pos = 0.0f;
    sscanf_s(iterator, "%f %f", &v_pos, &u_pos);
    texture_coordinates.emplace_back(v_pos, u_pos);
}

GLvoid Graphics::Tools::ObjParser::parseNormals(const char* iterator, std::vector<Math::Vector3f>& normals) noexcept
{
    GLfloat x_pos = 0.0f;
    GLfloat y_pos = 0.0f;
    GLfloat z_pos = 0.0f;
    sscanf_s(iterator, "%f %f %f", &x_pos, &y_pos, &z_pos);
    normals.emplace_back(x_pos, y_pos, z_pos);
}

GLvoid Graphics::Tools::ObjParser::parseFaceElementIndexes(const char* iterator, std::vector<Math::Vector3i>& face_element_indexes) noexcept
{
    GLint vertexIndex[Math::Vector3i::VECTOR_SIZE] = { 0 };
    GLint normalIndex[Math::Vector3i::VECTOR_SIZE] = { 0 };
    GLint textureCoordinateIndex[Math::Vector3i::VECTOR_SIZE] = { 0 };
    sscanf_s(iterator, "%i/%i/%i %i/%i/%i %i/%i/%i",
        &vertexIndex[0], &textureCoordinateIndex[0], &normalIndex[0],
        &vertexIndex[1], &textureCoordinateIndex[1], &normalIndex[1],
        &vertexIndex[2], &textureCoordinateIndex[2], &normalIndex[2]);
    face_element_indexes.emplace_back(vertexIndex[0], textureCoordinateIndex[0], normalIndex[0]);
    face_element_indexes.emplace_back(vertexIndex[1], textureCoordinateIndex[1], normalIndex[1]);
    face_element_indexes.emplace_back(vertexIndex[2], textureCoordinateIndex[2], normalIndex[2]);
}
