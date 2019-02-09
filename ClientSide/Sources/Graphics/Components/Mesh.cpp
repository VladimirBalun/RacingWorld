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
    glBufferData(GL_ARRAY_BUFFER, mCountElements * 4, mElements, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
        (void*)(ALIGNMENT_VERTEX * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, SIZE_ELEMENT * sizeof(GLfloat),
    //    (void*)(ALIGNMENT_COLOR * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, SIZE_ELEMENT * sizeof(GLfloat),
    //    (void*)(ALIGNMENT_TEXTURE_COORDINATE * sizeof(GLfloat)));
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, SIZE_ELEMENT * sizeof(GLfloat),
    //    (void*)(ALIGNMENT_NORMAL * sizeof(GLfloat)));
    //glEnableVertexAttribArray(3);

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
