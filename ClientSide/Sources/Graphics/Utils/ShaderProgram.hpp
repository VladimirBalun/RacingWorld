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

#include <string>
#include <sstream>
#include <iostream>

#include "../OpenGL.hpp"
#include "../../Utils/FileSystem.hpp"

namespace Graphics { namespace Utils {

    class ShaderProgram 
    {
    public:
        explicit ShaderProgram(const char* vShaderFileName, const char* fShaderFileName);
        GLvoid useShaderProgram();
    private:
        GLuint compileShader(const char* shaderSourcCode, GLint shaderType);
        GLvoid linkShaders(GLuint vertexShader, GLuint fragmentShader);
    private:
        GLuint mProgram;
    };

}}
