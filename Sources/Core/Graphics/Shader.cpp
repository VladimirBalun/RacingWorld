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

#include "PrecompiledHeader.hpp"
#include "Shader.hpp"

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Helpers/Debug.hpp"
#include "../Helpers/Macroses.hpp"
#include "../Resources/Text.hpp"

Core::Graphics::Shader::Shader(const Resources::VertexShaderSPtr vertex_shader, const Resources::FragmentShaderSPtr fragment_shader) noexcept
{
    const std::string& vertex_shader_data = vertex_shader->getData();
    const std::string& fragment_shader_data = fragment_shader->getData();
    const unsigned int vertex_shader_id = compileShader(vertex_shader_data.c_str(), GL_VERTEX_SHADER);
    const unsigned int fragment_shader_id = compileShader(fragment_shader_data.c_str(), GL_FRAGMENT_SHADER);
    linkShaders(vertex_shader_id, fragment_shader_id);
}

void Core::Graphics::Shader::use() const noexcept
{
    if (isValid())
    {
        glUseProgram(m_program_id);
    }
    else
    {
        LOG_WARNING("Shader program is invalid, could not used it.");
    }
}

bool Core::Graphics::Shader::isValid() const noexcept
{
    return m_program_id != 0;
}

void Core::Graphics::Shader::setUniformf(const char* name, const float value) const noexcept
{
    const unsigned int location_id = glGetUniformLocation(m_program_id, name);
    glUniform1f(location_id, value);
}

void Core::Graphics::Shader::setUniformVector3f(const char* name, const glm::vec3& vector) const noexcept
{
    const unsigned int location_id = glGetUniformLocation(m_program_id, name);
    glUniform3f(location_id, vector.x, vector.y, vector.z);
}

void Core::Graphics::Shader::setUniformMatrix4x4f(const char* name, const glm::mat3& matrix) const noexcept
{
    const unsigned int location_id = glGetUniformLocation(m_program_id, name);
    glUniformMatrix4fv(location_id, 1, GL_TRUE, glm::value_ptr(matrix));
}

unsigned int Core::Graphics::Shader::compileShader(const std::string& shader_data, const int shader_type) noexcept
{
    const unsigned int shader = glCreateShader(shader_type);
    const char* buffer = shader_data.c_str();

    glShaderSource(shader, 1, &buffer, NULL);
    glCompileShader(shader);

#ifdef _DEBUG
    int was_compiled_shader = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &was_compiled_shader);
    if (!was_compiled_shader)
    {
        std::array<char, 512> error_log{};
        glGetProgramInfoLog(shader, error_log.max_size(), NULL, error_log.data());
        LOG_WARNING("Shader was not compiled. Cause:" + STR(error_log.data()));
    }
#endif // _DEBUG

    return shader;
}

void Core::Graphics::Shader::linkShaders(const unsigned int vertex_shader, const unsigned int fragment_shader) noexcept
{
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader);
    glAttachShader(m_program_id, fragment_shader);
    glLinkProgram(m_program_id);

#ifdef _DEBUG
    int were_linked_shaders = 0;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &were_linked_shaders);
    if (!were_linked_shaders)
    {
        std::array<char, 512> error_log{};
        glGetProgramInfoLog(m_program_id, error_log.max_size(), NULL, error_log.data());
        LOG_WARNING("Shaders were not linked. Cause:" + STR(error_log.data()));
    }
#endif // _DEBUG

    glDetachShader(m_program_id, vertex_shader);
    glDetachShader(m_program_id, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Core::Graphics::Shader::~Shader()
{
    glDeleteProgram(m_program_id);
}
