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

Core::Graphics::SceneGraph::Mesh::Mesh(std::vector<float>&& elements, unsigned count_elements) noexcept
    : m_elements(elements), m_count_elements(count_elements)
{
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);

#ifdef _DEBUG
    LOG_WARNING_IF(m_vao == 0, "ID for vertex array objects was not generated.");
    LOG_WARNING_IF(m_vbo == 0, "ID for vertex buffer object was not generated.");
#endif // _DEBUG

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<ptrdiff_t>(m_count_elements * SIZE_ELEMENT * sizeof(float)), m_elements.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(float), reinterpret_cast<void*>(ALIGNMENT_VERTEX * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(float), reinterpret_cast<void*>(ALIGNMENT_TEXTURE_COORDINATE * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(float), reinterpret_cast<void*>(ALIGNMENT_NORMAL * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void Core::Graphics::SceneGraph::Mesh::draw() const noexcept
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_count_elements);
    glBindVertexArray(NULL);
}

Core::Graphics::SceneGraph::Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
