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

#include <array>
#include <string>
#include <vector>

#include "../OpenGL.hpp"
#include "../../Utils/FileSystem.hpp"
#include "../../Math/Vectors.hpp"
#include "../../Math/Matrices.hpp"
#include "../../EventSystem/EventManager.hpp"

namespace Graphics { namespace Tools {

    class ShaderProgram 
    {
    public:
        explicit ShaderProgram() noexcept = default;
        explicit ShaderProgram(const std::string& v_shader_fileName, const std::string& f_shader_fileName) noexcept;
        GLvoid use() const noexcept;
        GLvoid destroy() const noexcept;
        GLuint getProgramID() const noexcept;
        GLboolean isInitialized() const noexcept;
        GLvoid setUniformf(const char* name, GLfloat value) const noexcept;
        GLvoid setUniformVector3f(const char* name, const Math::Vector3<GLfloat>& vector) const noexcept;
        GLvoid setUniformMatrix4x4f(const char* name, const Math::Matrix4x4<GLfloat>& matrix) const noexcept;
    private:
        GLuint compileShader(const std::vector<char>& shader_source_code, GLint shader_type) noexcept;
        GLvoid linkShaders(GLuint vertex_shader, GLuint fragment_shader) noexcept;
        GLint getAttributeLocation(const char* name) const noexcept;
        GLint getUniformLocation(const char* name) const noexcept;
    private:
        GLuint m_program_id = 0;
    };

}}
