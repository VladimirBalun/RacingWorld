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

#include "OpenGL.hpp"

PFNGLDRAWRANGEELEMENTSPROC __glDrawRangeElements = nullptr;

static GLboolean initOpenGL_1_2()
{
    GLboolean result = GL_TRUE;
    return result;
}

static GLboolean initOpenGL_1_3()
{
    GLboolean result = GL_TRUE;
    return result;
}

// ...

PFNGLCREATESHADERPROC __glCreateShader = nullptr;

static GLboolean initOpenGL_2_0()
{
    GLboolean result = GL_TRUE;
    result = ((glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"))) != nullptr) & result;
    return result;
}

// ...

GLvoid initOpenGL()
{
    if (!initOpenGL_1_2())
        throw std::runtime_error("Opengl version of 1.2 was not initialized.");
    if (!initOpenGL_1_3())
        throw std::runtime_error("Opengl version of 1.3 was not initialized.");
    if (!initOpenGL_2_0())
        throw std::runtime_error("Opengl version of 2.0 was not initialized.");
}
