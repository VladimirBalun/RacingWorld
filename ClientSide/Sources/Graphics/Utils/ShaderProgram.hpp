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
#include "../../Math/Vector2.hpp"
#include "../../Math/Vector3.hpp"
#include "../../Math/Vector4.hpp"
#include "../../Math/Matrix2x2.hpp"
#include "../../Math/Matrix3x3.hpp"
#include "../../Math/Matrix4x4.hpp"

namespace Graphics { namespace Utils {

    class ShaderProgram 
    {
    public:
        explicit ShaderProgram(const char* vShaderFileName, const char* fShaderFileName);
        ShaderProgram();
        ~ShaderProgram();
        void destroyProgram();
        void destroyProgram(UINT idProgram);
        void setProgram() const noexcept;
        void setProgram(UINT idProgram);
        void unsetProgram();
        GLuint getProgram();

        GLuint getAttribLocation(const char* name) const;
        GLuint getUniformLocation(const char* name) const;

        template<typename Type> void setUniform(const char* name, Type value) const noexcept;
        template<typename Type> void setUniformVector(const char* name, const Math::Vector2<Type>& vector) const noexcept;
        template<typename Type> void setUniformVector(const char* name, const Math::Vector3<Type>& vector) const noexcept;
        template<typename Type> void setUniformVector(const char* name, const Math::Vector4<Type>& vector) const noexcept;

        template<typename Type> void setUniformMatrix(const char* name, const Math::Matrix2x2<Type>& matrix) const noexcept;
        template<typename Type> void setUniformMatrix(const char* name, const Math::Matrix3x3<Type>& matrix) const noexcept;
        template<typename Type> void setUniformMatrix(const char* name, const Math::Matrix4x4<Type>& matrix) const noexcept;
    private:
        GLuint compileShader(const char* shaderSourcCode, GLint shaderType);
        GLvoid linkShaders(GLuint vertexShader, GLuint fragmentShader);
    private:
        GLuint mProgram;
    };

}}
