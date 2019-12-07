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

#include "PrecompiledHeader.hpp"
#include "Mesh.hpp"

#include <glew.h>

#include "../../Helpers/Debug.hpp"

Core::Graphics::SceneGraph::Mesh::Mesh(Texture2D texture, std::vector<float>&& elements, unsigned count_elements) noexcept
    : m_texture(texture), m_elements(elements), m_count_elements(count_elements)
{
    generateIdentifiers();
    bindDataIdentifiers();
    fillBuffersData();
    unbindDataIdentifiers();
}

void Core::Graphics::SceneGraph::Mesh::draw() const noexcept
{
    m_texture.bind();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_count_elements);
    glBindVertexArray(NULL);
    m_texture.unbind();
}

void Core::Graphics::SceneGraph::Mesh::free() noexcept
{
#ifdef _DEBUG
    unsigned int result = 0u;
#endif // _DEBUG

    glDeleteBuffers(1, &m_vbo);
#ifdef _DEBUG
    LOG_WARNING_IF((result = glGetError()) == GL_INVALID_VALUE, "VBO data were not deleted.");
#endif // _DEBUG

    glDeleteVertexArrays(1, &m_vao);
#ifdef _DEBUG
    LOG_WARNING_IF((result = glGetError()) == GL_INVALID_VALUE, "VAO data were not deleted.");
#endif // _DEBUG

    m_texture.free();
    m_elements.shrink_to_fit();

    m_vbo = 0u;
    m_vao = 0u;
    m_count_elements = 0u;
}

void Core::Graphics::SceneGraph::Mesh::generateIdentifiers()
{
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);

#ifdef _DEBUG
    LOG_WARNING_IF(m_vao == 0, "ID for vertex array objects was not generated.");
    LOG_WARNING_IF(m_vbo == 0, "ID for vertex buffer object was not generated.");
#endif // _DEBUG
}

void Core::Graphics::SceneGraph::Mesh::bindDataIdentifiers()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void Core::Graphics::SceneGraph::Mesh::unbindDataIdentifiers()
{
    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void Core::Graphics::SceneGraph::Mesh::fillBuffersData()
{
    constexpr std::uint8_t ALIGNMENT_VERTEX = 0u;
    constexpr std::uint8_t ALIGNMENT_TEXTURE_COORDINATE = 3u;
    constexpr std::uint8_t ALIGNMENT_NORMAL = 5u;
    constexpr std::uint8_t SIZE_ELEMENT = ALIGNMENT_NORMAL + 3u;

    glBufferData(GL_ARRAY_BUFFER, static_cast<ptrdiff_t>(m_count_elements * SIZE_ELEMENT * sizeof(float)), 
        m_elements.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(float), reinterpret_cast<void*>(ALIGNMENT_VERTEX * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(float), reinterpret_cast<void*>(ALIGNMENT_TEXTURE_COORDINATE * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(float), reinterpret_cast<void*>(ALIGNMENT_NORMAL * sizeof(float)));
    glEnableVertexAttribArray(2);
}
