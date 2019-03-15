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

#include "ShaderProgram.hpp"

Graphics::Tools::ShaderProgram::ShaderProgram(Memory::Allocators::LinearAllocator& allocator, const char* vShaderFileName, const char* fShaderFileName)
{
    const char* vShaderSourceCode = Utils::readFile(vShaderFileName,
        std::bind(&Memory::Allocators::LinearAllocator::allocate, &allocator, std::placeholders::_1));
    const char* fShaderSourceCode = Utils::readFile(fShaderFileName,
        std::bind(&Memory::Allocators::LinearAllocator::allocate, &allocator, std::placeholders::_1));

    if (!vShaderSourceCode)
        EventSystem::EventManager::getInstance().notifyGlobalError("Vertex shader was not read.");
    if (!fShaderSourceCode)
        EventSystem::EventManager::getInstance().notifyGlobalError("Fragment shader was not read.");

    const GLuint vertexShader = compileShader(vShaderSourceCode, GL_VERTEX_SHADER);
    const GLuint fragmentShader = compileShader(fShaderSourceCode, GL_FRAGMENT_SHADER);
    linkShaders(vertexShader, fragmentShader);
}

GLuint Graphics::Tools::ShaderProgram::compileShader(const char* shaderSourceCode, GLint shaderType) noexcept
{
    const GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCode, NULL);
    glCompileShader(shader);

#ifdef _DEBUG
    GLint isCompiledShader;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiledShader);
    if (!isCompiledShader)
    {
        GLchar errorLog[512];
        glGetShaderInfoLog(shader, 512, NULL, errorLog);
        LOG_WARNING(errorLog);
    }
#endif // _DEBUG

    return shader;
}

GLvoid Graphics::Tools::ShaderProgram::linkShaders(GLuint vertexShader, GLuint fragmentShader) noexcept
{
    mProgramID = glCreateProgram();
    glAttachShader(mProgramID, vertexShader);
    glAttachShader(mProgramID, fragmentShader);
    glLinkProgram(mProgramID);

#ifdef _DEBUG
    GLint isLinkedShaders;
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &isLinkedShaders);
    if (!isLinkedShaders)
    {
        GLchar errorLog[512];
        glGetProgramInfoLog(mProgramID, 512, NULL, errorLog);
        LOG_WARNING(errorLog);
    }
#endif // _DEBUG

    glDetachShader(mProgramID, vertexShader);
    glDetachShader(mProgramID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLboolean Graphics::Tools::ShaderProgram::isInitialized() const noexcept
{
    return mProgramID != 0;
}

GLvoid Graphics::Tools::ShaderProgram::use() const noexcept
{
    glUseProgram(mProgramID);
}

GLvoid Graphics::Tools::ShaderProgram::destroy() const noexcept
{
    glDeleteProgram(mProgramID);
}

GLuint Graphics::Tools::ShaderProgram::getProgramID() const noexcept
{
    return mProgramID;
}

GLint Graphics::Tools::ShaderProgram::getAttributeLocation(const char* name) const noexcept
{
    GLint locationID = glGetAttribLocation(mProgramID, name);

#ifdef  _DEBUG
    if (locationID == -1)
        LOG_WARNING("Location of attribute was not found.");
#endif // _DEBUG

    return locationID;
}

GLint Graphics::Tools::ShaderProgram::getUniformLocation(const char* name) const noexcept
{
    GLint locationID = glGetUniformLocation(mProgramID, name);

#ifdef  _DEBUG
    if (locationID == -1)
        LOG_WARNING("Location of uniform was not found.");
#endif // _DEBUG

    return locationID;
}

GLvoid Graphics::Tools::ShaderProgram::setUniformf(const char* name, GLfloat value) const noexcept
{
    glUseProgram(mProgramID);
    glUniform1f(getUniformLocation(name), value);
}

GLvoid Graphics::Tools::ShaderProgram::setUniformVector3f(const char* name, const Math::Vector3<GLfloat>& vector) const noexcept
{
    glUseProgram(mProgramID);
    glUniform3f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
}

GLvoid Graphics::Tools::ShaderProgram::setUniformMatrix4x4f(const char* name, const Math::Matrix4x4<GLfloat>& matrix) const noexcept
{
    GLfloat array[Math::Matrix4x4<GLfloat>::MATRIX_SIZE];
    matrix.toArray(array);
    glUseProgram(mProgramID);
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, array);
}
