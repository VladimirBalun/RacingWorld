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

#include "Mesh.hpp"

static const std::uint8_t ALIGNMENT_VERTEX = 0;
static const std::uint8_t ALIGNMENT_TEXTURE_COORDINATE = 3;
static const std::uint8_t ALIGNMENT_NORMAL = 5;
static constexpr std::uint8_t SIZE_ELEMENT = ALIGNMENT_NORMAL + 3;

Graphics::Components::Mesh::Mesh(std::vector<Math::Vector3f>&& vertices, std::vector<Math::Vector2f>&& texture_coordinates,
    std::vector<Math::Vector3f>&& normals, std::vector<Math::Vector3i>&& face_element_indexes) noexcept : m_count_elements(face_element_indexes.size())
{
    const std::size_t memory_size = static_cast<GLuint>(face_element_indexes.size() * (SIZE_ELEMENT * sizeof(GLfloat)));
    m_elements = new GLfloat[memory_size];
    GLuint inner_alignment_for_elements = 0;
    for (GLuint i = 0; i < face_element_indexes.size(); i++)
    {
        GLint vertex_index = face_element_indexes.at(i).getX();
        GLint texture_coordinate_index = face_element_indexes.at(i).getY();
        GLint normal_index = face_element_indexes.at(i).getZ();
        vertices[vertex_index].toArray(m_elements + inner_alignment_for_elements + ALIGNMENT_VERTEX);
        texture_coordinates[texture_coordinate_index].toArray(m_elements + inner_alignment_for_elements + ALIGNMENT_TEXTURE_COORDINATE);
        normals[normal_index].toArray(m_elements + inner_alignment_for_elements + ALIGNMENT_NORMAL);
        inner_alignment_for_elements += SIZE_ELEMENT;
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbO);

#ifdef _DEBUG
    if (m_vao == 0)
        LOG_WARNING("ID for vertex array objects was not generated.");
    if (m_vbO == 0)
        LOG_WARNING("ID for vertex buffer object was not generated.");
#endif // _DEBUG

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_count_elements * SIZE_ELEMENT * sizeof(GLfloat)), m_elements, GL_STATIC_DRAW);

    glVertexAttribPointer(0, Math::Vector3f::VECTOR_SIZE, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(GLfloat), reinterpret_cast<void*>(ALIGNMENT_VERTEX * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, Math::Vector2f::VECTOR_SIZE, GL_FLOAT, GL_FALSE, 
        SIZE_ELEMENT * sizeof(GLfloat), reinterpret_cast<void*>(ALIGNMENT_TEXTURE_COORDINATE * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, Math::Vector3f::VECTOR_SIZE, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(GLfloat), reinterpret_cast<void*>(ALIGNMENT_NORMAL * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

GLvoid Graphics::Components::Mesh::setMaterial(const Material& material) noexcept
{
    m_material = material;
}

const std::optional<Graphics::Components::Material>& Graphics::Components::Mesh::getMaterial() const noexcept
{
    return m_material;
}

GLvoid Graphics::Components::Mesh::draw() const noexcept
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_count_elements);
    glBindVertexArray(NULL);
}

GLvoid Graphics::Components::Mesh::destroy() const noexcept
{
    glDeleteBuffers(1, &m_vbO);
    glDeleteVertexArrays(1, &m_vao);
}
