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

Graphics::Components::Mesh::Mesh(GLfloat* elements, std::size_t countElements) :
    mElements(elements), mCountElements(countElements)
{
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

#ifdef _DEBUG
    if (mVAO == 0)
        LOG_WARNING("ID for vertex array objects was not generated.");
    if (mVBO == 0)
        LOG_WARNING("ID for vertex buffer object was not generated.");
#endif // _DEBUG

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mCountElements * SIZE_ELEMENT * sizeof(GLfloat), mElements, GL_STATIC_DRAW);

#ifdef _DEBUG
    switch (glGetError())
    {
    case GL_INVALID_ENUM:
        LOG_WARNING("Target is not GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER or "
            "usage is not GL_STREAM_DRAW, GL_STATIC_DRAW, or GL_DYNAMIC_DRAW.");
        break;
    case GL_INVALID_VALUE:
        LOG_WARNING("Size is negative.");
        break;
    case GL_INVALID_OPERATION:
        LOG_WARNING("The reserved buffer object name 0 is bound to target.");
        break;
    case GL_OUT_OF_MEMORY:
        LOG_WARNING("GL is unable to create a data store with the specified size.");
    }
#endif // _DEBUG

    glVertexAttribPointer(0, Math::Vector3f::VECTOR_SIZE, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(GLfloat), (void*)(ALIGNMENT_VERTEX * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, Math::Vector2f::VECTOR_SIZE, GL_FLOAT, GL_FALSE, 
        SIZE_ELEMENT * sizeof(GLfloat), (void*)(ALIGNMENT_TEXTURE_COORDINATE * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(3, Math::Vector3f::VECTOR_SIZE, GL_FLOAT, GL_FALSE,
        SIZE_ELEMENT * sizeof(GLfloat), (void*)(ALIGNMENT_NORMAL * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

#ifdef _DEBUG
    switch (glGetError())
    {
    case GL_INVALID_VALUE:
        LOG_WARNING("Index is greater than or equal to GL_MAX_VERTEX_ATTRIBS or"
            "size is not 1, 2, 3, 4 or (for glVertexAttribPointer), GL_BGRA or"
            "stride is negative.");
        break;
    case GL_INVALID_ENUM:
        LOG_WARNING("Type is not an accepted value.");
        break;
    case GL_INVALID_OPERATION:
        LOG_WARNING("Size is GL_BGRA and type is not GL_UNSIGNED_BYTE, GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV or "
            "type is GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV and size is not 4 or GL_BGRA or "
            "type is GL_UNSIGNED_INT_10F_11F_11F_REV and size is not 3 or "
            "size is GL_BGRA and noramlized is GL_FALSE or "
            "zero is bound to the GL_ARRAY_BUFFER buffer object binding point and the pointer argument is not NULL.");
    }
#endif // _DEBUG

    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

GLboolean Graphics::Components::Mesh::isInitialized() const noexcept
{
    return mElements != nullptr;
}

GLvoid Graphics::Components::Mesh::draw() const noexcept
{
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mCountElements);
    glBindVertexArray(NULL);
}

GLvoid Graphics::Components::Mesh::destroy() const noexcept
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}
