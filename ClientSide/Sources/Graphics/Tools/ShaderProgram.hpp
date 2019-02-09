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

#include "../OpenGL.hpp"
#include "../../Utils/FileSystem.hpp"
#include "../../Math/Vectors.hpp"
#include "../../Math/Matrices.hpp"
#include "../../Memory/LinearAllocator.hpp"

namespace Graphics { namespace Tools {

    class ShaderProgram 
    {
    public:
        ShaderProgram() = default;
        ShaderProgram(Memory::LinearAllocator& allocator, const char* vShaderFileName, const char* fShaderFileName);
        
        GLvoid use() const noexcept;
        GLvoid destroy() const noexcept;
        GLuint getProgramID() const noexcept;
        GLboolean isInitialized() const noexcept;

        template<typename Type>
        GLvoid setUniform(const char* name, Type value) const noexcept;
        template<typename Type>
        GLvoid setUniformVector(const char* name, const Math::Vector2<Type>& vector) const noexcept;
        template<typename Type>
        GLvoid setUniformVector(const char* name, const Math::Vector3<Type>& vector) const noexcept;
        template<typename Type>
        GLvoid setUniformVector(const char* name, const Math::Vector4<Type>& vector) const noexcept;

        template<typename Type>
        GLvoid setUniformMatrix(const char* name, const Math::Matrix2x2<Type>& matrix) const noexcept;
        template<typename Type>
        GLvoid setUniformMatrix(const char* name, const Math::Matrix3x3<Type>& matrix) const noexcept;
        template<typename Type> 
        GLvoid setUniformMatrix(const char* name, const Math::Matrix4x4<Type>& matrix) const noexcept;
    private:
        GLuint compileShader(const char* shaderSourceCode, GLint shaderType) noexcept;
        GLvoid linkShaders(GLuint vertexShader, GLuint fragmentShader) noexcept;
        GLint getAttributeLocation(const char* name) const noexcept;
        GLint getUniformLocation(const char* name) const noexcept;
    private:
        GLuint mProgramID = 0;
    };

}}
