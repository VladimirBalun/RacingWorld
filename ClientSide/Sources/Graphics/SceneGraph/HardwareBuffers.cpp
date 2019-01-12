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

#include "VertexBuffers.hpp"


Graphics::SceneGraph::HardwareBuffers::HardwareBuffers()
{
    glGenVertexArrays(1, &mVAOID);
    glBindVertexArray(mVAOID);
    isEBO = false;
}

void Graphics::SceneGraph::HardwareBuffers::createBuffers3f(const GLuint location, GLsizeiptr size, const void *data)
{
    _createArrayBuffers(3, GL_FLOAT, location, size, data);
}

void Graphics::SceneGraph::HardwareBuffers::_createArrayBuffers(GLint count, GLenum type, const GLuint location, GLsizeiptr size, const void * data)
{
    unsigned int vbo = 0;
    glGenBuffers(1, &vbo);
    VBOs.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    if (location != -1)
    {
        glVertexAttribPointer(location, count, type, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(location);
        //LocAttribs.push_back(location);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Graphics::SceneGraph::HardwareBuffers::createIndexBuffer(GLsizeiptr size, const void * data)
{
    isEBO = true;
    unsigned int ebo = 0;
    glGenBuffers(1, &ebo);
    VBOs.push_back(ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

bool Graphics::SceneGraph::HardwareBuffers::isIndexBuffer()
{
    return isEBO;
}

void Graphics::SceneGraph::HardwareBuffers::bind()
{
    // for (int n : LocAttribs) 
    //  glEnableVertexAttribArray(n);
    glBindVertexArray(mVAOID);
}

void Graphics::SceneGraph::HardwareBuffers::unbind()
{
    // for (int n : LocAttribs)
    //  glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
 
Graphics::SceneGraph::HardwareBuffers::~HardwareBuffers()
{
    unbind();
    glDeleteVertexArrays(1, &mVAOID);

    for (GLuint id_vbo : VBOs)
        glDeleteBuffers(1, &id_vbo);

    VBOs.clear();
}

