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

#include <iostream>
#include "ShaderProgram.hpp"

Graphics::Tools::ShaderProgram::ShaderProgram(const std::string& v_shader_fileName, const std::string& f_shader_fileName) noexcept
{
    const std::vector<char> v_shader_source_code(Utils::readFile(v_shader_fileName));
    const std::vector<char> f_shader_source_code(Utils::readFile(f_shader_fileName));

    if (v_shader_source_code.empty())
        EventSystem::EventManager::getInstance().notifyGlobalError("Vertex shader was not read.");
    if (f_shader_source_code.empty())
        EventSystem::EventManager::getInstance().notifyGlobalError("Fragment shader was not read.");

    const GLuint vertex_shader = compileShader(v_shader_source_code, GL_VERTEX_SHADER);
    const GLuint fragment_shader = compileShader(f_shader_source_code, GL_FRAGMENT_SHADER);
    linkShaders(vertex_shader, fragment_shader);
}

GLuint Graphics::Tools::ShaderProgram::compileShader(const std::vector<char>& shader_source_code, GLint shader_type) noexcept
{
    const GLuint shader = glCreateShader(shader_type);
    const char* buffer = shader_source_code.data();

    glShaderSource(shader, 1, &buffer, NULL);
    glCompileShader(shader);

#ifdef _DEBUG
    GLint is_compiled_shader;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled_shader);
    if (!is_compiled_shader)
    {
        char error_log[512] = { 0 };
        glGetProgramInfoLog(shader, 512, NULL, error_log);
        LOG_WARNING(error_log);
    }
#endif // _DEBUG

    return shader;
}

GLvoid Graphics::Tools::ShaderProgram::linkShaders(GLuint vertex_shader, GLuint fragment_shader) noexcept
{
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader);
    glAttachShader(m_program_id, fragment_shader);
    glLinkProgram(m_program_id);

#ifdef _DEBUG
    GLint is_linked_shaders;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &is_linked_shaders);
    if (!is_linked_shaders)
    {
        std::array<char, 512> error_log{};
        glGetProgramInfoLog(m_program_id, error_log.max_size(), NULL, error_log.data());
        LOG_WARNING(error_log.data());
    }
#endif // _DEBUG

    glDetachShader(m_program_id, vertex_shader);
    glDetachShader(m_program_id, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

GLboolean Graphics::Tools::ShaderProgram::isInitialized() const noexcept
{
    return m_program_id != 0;
}

GLvoid Graphics::Tools::ShaderProgram::use() const noexcept
{
    glUseProgram(m_program_id);
}

GLvoid Graphics::Tools::ShaderProgram::destroy() const noexcept
{
    glDeleteProgram(m_program_id);
}

GLuint Graphics::Tools::ShaderProgram::getProgramID() const noexcept
{
    return m_program_id;
}

GLint Graphics::Tools::ShaderProgram::getAttributeLocation(const char* name) const noexcept
{
    GLint location_id = glGetAttribLocation(m_program_id, name);

#ifdef  _DEBUG
    if (location_id == -1)
        LOG_WARNING("Location of attribute was not found.");
#endif // _DEBUG

    return location_id;
}

GLint Graphics::Tools::ShaderProgram::getUniformLocation(const char* name) const noexcept
{
    GLint location_id = glGetUniformLocation(m_program_id, name);

#ifdef  _DEBUG
    if (location_id == -1)
        LOG_WARNING("Location of uniform was not found.");
#endif // _DEBUG

    return location_id;
}

GLvoid Graphics::Tools::ShaderProgram::setUniformf(const char* name, GLfloat value) const noexcept
{
    glUseProgram(m_program_id);
    glUniform1f(getUniformLocation(name), value);
}

GLvoid Graphics::Tools::ShaderProgram::setUniformVector3f(const char* name, const Math::Vector3<GLfloat>& vector) const noexcept
{
    glUseProgram(m_program_id);
    glUniform3f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
}

GLvoid Graphics::Tools::ShaderProgram::setUniformMatrix4x4f(const char* name, const Math::Matrix4x4<GLfloat>& matrix) const noexcept
{
    std::array<GLfloat, Math::Matrix4x4<GLfloat>::MATRIX_SIZE> array{};
    matrix.toArray(array.data());
    glUseProgram(m_program_id);
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, array.data());
}
