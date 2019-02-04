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

#pragma once

#include <vector>

#include "../OpenGL.hpp"
#include "../../Utils/Debug.hpp"


namespace Graphics { namespace Tools {

    enum BufferType 
    {
        ArrayBuffer,
        IndexBuffer
    };

    enum DrawType 
    {
        STATIC  =  GL_STATIC_DRAW,
        DYNAMIC =  GL_DYNAMIC_DRAW,
        STREAM  =  GL_STREAM_DRAW
    };

    enum VariableType 
    {
        VT_BYTE  = GL_BYTE,
        VT_UBYTE = GL_UNSIGNED_BYTE,
        VT_SHORT  = GL_SHORT,
        VT_USHORT = GL_UNSIGNED_SHORT,
        VT_FLOAT = GL_FLOAT,
        VT_INT  = GL_INT,
        VT_UINT = GL_UNSIGNED_INT
    };

    class HardwareBuffers
    {
    public:
        HardwareBuffers();
        void createBuffers3f(const GLuint location, GLsizeiptr size, const void *data);
        void createIndexBuffer(GLsizeiptr size, const void *data);
        bool isIndexBuffer();
        void bind();
        void unbind();
         ~HardwareBuffers();
    private:
        void _createArrayBuffers(GLint count, GLenum type, const GLuint location, GLsizeiptr size, const void *data);
    private:
        GLuint mVAOID;
        std::vector<GLuint> VBOs;
        bool isEBO;
    };
 }}
