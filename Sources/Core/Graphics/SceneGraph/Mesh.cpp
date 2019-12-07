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
#include "../../Resources/Image.hpp"

Core::Graphics::SceneGraph::Mesh::Mesh(Resources::ImageSPtr texture, std::vector<float>&& elements, unsigned count_elements) noexcept
    : m_elements(elements), m_count_elements(count_elements)
{
    generateIdentifiers();
    bindDataIdentifiers();
    fillTextureData(texture);
    fillBuffersData();
    unbindDataIdentifiers();
}

void Core::Graphics::SceneGraph::Mesh::draw() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_count_elements);
    glBindVertexArray(NULL);
    glBindTexture(GL_TEXTURE_2D, NULL);
}

Core::Graphics::SceneGraph::Mesh::~Mesh()
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

    glDeleteTextures(1, &m_texture);
#ifdef _DEBUG
    LOG_WARNING_IF((result = glGetError()) == GL_INVALID_VALUE, "Texture data were not deleted.");
#endif // _DEBUG
}

void Core::Graphics::SceneGraph::Mesh::generateIdentifiers()
{
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);
    glGenTextures(1, &m_texture);

#ifdef _DEBUG
    LOG_WARNING_IF(m_vao == 0, "ID for vertex array objects was not generated.");
    LOG_WARNING_IF(m_vbo == 0, "ID for vertex buffer object was not generated.");
    LOG_WARNING_IF(m_texture == 0, "ID for texture was not generated.");
#endif // _DEBUG
}

void Core::Graphics::SceneGraph::Mesh::bindDataIdentifiers()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Core::Graphics::SceneGraph::Mesh::unbindDataIdentifiers()
{
    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void Core::Graphics::SceneGraph::Mesh::fillTextureData(Resources::ImageSPtr texture)
{
    if (texture)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        const std::uint16_t texture_width = texture->getWidth();
        const std::uint16_t texture_height = texture->getHeight();
        const unsigned char* texture_data = texture->getData();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
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
