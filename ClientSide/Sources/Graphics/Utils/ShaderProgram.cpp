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

Graphics::Utils::ShaderProgram::ShaderProgram(const char* vShaderFileName, const char* fShaderFileName)
{
    // TODO: need to fix reallocation of string
    const char* vShaderSourceCode = _strdup(readFile(vShaderFileName).c_str());
    const char* fShaderSourceCode = _strdup(readFile(fShaderFileName).c_str());

    const GLuint vertexShader = compileShader(vShaderSourceCode, GL_VERTEX_SHADER);
    const GLuint fragmantShader = compileShader(fShaderSourceCode, GL_FRAGMENT_SHADER);
    linkShaders(vertexShader, fragmantShader);
    glDetachShader(mProgram, vertexShader);
    glDetachShader(mProgram, fragmantShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmantShader);

    free((void*) vShaderSourceCode);
    free((void*) fShaderSourceCode);
}

Graphics::Utils::ShaderProgram::ShaderProgram()
{
    unsetProgram();
    mProgram = -1;
}

GLuint Graphics::Utils::ShaderProgram::compileShader(const char* shaderSourceCode, GLint shaderType)
{
    GLint isCompiledShader;
    const GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiledShader);

    if (!isCompiledShader)
    {
        GLchar errorLog[512];
        glGetShaderInfoLog(shader, 512, NULL, errorLog);
        LOG_WARNING("Shader was not compiled. Cause: " + std::string(errorLog));
    }

    return shader;
}

GLvoid Graphics::Utils::ShaderProgram::linkShaders(GLuint vertexShader, GLuint fragmentShader)
{
    GLint isLinkedShaders;
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &isLinkedShaders);

    if (!isLinkedShaders) 
    {
        GLchar errorLog[512];
        glGetProgramInfoLog(mProgram, 512, NULL, errorLog);
        LOG_WARNING(std::string("Shaders were not linked. Cause: ") + std::string(errorLog));
    }
}

void Graphics::Utils::ShaderProgram::destroyProgram()
{
    glDeleteProgram(mProgram);
}

void Graphics::Utils::ShaderProgram::destroyProgram(UINT idProgram)
{
    glDeleteProgram(idProgram);
}

Graphics::Utils::ShaderProgram::~ShaderProgram()
{
    //destroyProgram();
}

void Graphics::Utils::ShaderProgram::setProgram() const noexcept
{
    glUseProgram(mProgram);
}

void Graphics::Utils::ShaderProgram::setProgram(UINT idProgram)
{
    mProgram = idProgram;
    setProgram();
}

void Graphics::Utils::ShaderProgram::unsetProgram()
{
    glUseProgram(NULL);
}

GLuint Graphics::Utils::ShaderProgram::getProgram() 
{
    return mProgram;
}

GLuint Graphics::Utils::ShaderProgram::getAttribLocation(const char* name) const
{
    return glGetAttribLocation(mProgram, name);
}

GLuint Graphics::Utils::ShaderProgram::getUniformLocation(const char* name) const
{
    return glGetUniformLocation(mProgram, name);
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniform(const char* name, Type value) const noexcept
{
    setProgram();
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniform1f(getUniformLocation(name), value);
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniform1d(getUniformLocation(name), value);
    else if constexpr (std::is_same<Type, GLint>::value)
        glUniform1i(getUniformLocation(name), value);
    else if constexpr (std::is_same<Type, GLboolean>::value)
        glUniform1i(getUniformLocation(name), static_cast<GLint>(value));
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniformVector(const char* name, const Math::Vector2<Type> &vector) const noexcept
{
    setProgram();
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniform2f(getUniformLocation(name), vector.getX() , vector.getY());
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniform2d(getUniformLocation(name), vector.getX() , vector.getY());
    else if constexpr (std::is_same<Type, GLint>::value)
        glUniform2i(getUniformLocation(name), vector.getX() , vector.getY());
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniformVector(const char* name, const Math::Vector3<Type>& vector) const noexcept
{
    setProgram();
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniform3f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniform3d(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
    else if constexpr (std::is_same<Type, GLint>::value)
        glUniform3i(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniformVector(const char* name, const Math::Vector4<Type>& vector) const noexcept
{
    setProgram();
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniform4f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ(), vector.getW());
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniform4d(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ(), vector.getW());
    else if constexpr (std::is_same<Type, GLint>::value)
        glUniform4i(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ(), vector.getW());
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniformMatrix(const char* name, const Math::Matrix2x2<Type>& matrix) const noexcept
{
    setProgram();
    Type array[Math::Matrix2x2<Type>::MATRIX_SIZE];
    matrix.toArray(array);
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, array);
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniformMatrix2dv(getUniformLocation(name), 1, GL_FALSE, array);
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniformMatrix(const char* name, const Math::Matrix3x3<Type>& matrix) const noexcept
{
    setProgram();
    Type array[Math::Matrix3x3<Type>::MATRIX_SIZE];
    matrix.toArray(array);
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, array);
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniformMatrix3dv(getUniformLocation(name), 1, GL_FALSE, array);
}

template<typename Type>
void Graphics::Utils::ShaderProgram::setUniformMatrix(const char* name, const Math::Matrix4x4<Type>& matrix) const noexcept
{
    setProgram();
    Type array[Math::Matrix4x4<Type>::MATRIX_SIZE];
    matrix.toArray(array);
    if constexpr (std::is_same<Type, GLfloat>::value)
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, array);
    else if constexpr (std::is_same<Type, GLdouble>::value)
        glUniformMatrix4dv(getUniformLocation(name), 1, GL_TRUE, array);
}

template void Graphics::Utils::ShaderProgram::setUniform<GLfloat>(const char* name, GLfloat value) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniform<GLdouble>(const char* name, GLdouble value) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniform<GLint>(const char* name, GLint value) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniform<GLboolean>(const char* name, GLboolean value) const noexcept;

template void Graphics::Utils::ShaderProgram::setUniformVector<GLfloat>(const char* name, const Math::Vector2f& vector) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformVector<GLdouble>(const char* name, const Math::Vector2d& vector) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformVector<GLint>(const char* name, const Math::Vector2i& vector) const noexcept;

template void Graphics::Utils::ShaderProgram::setUniformVector<GLfloat>(const char* name, const Math::Vector3f& vector) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformVector<GLdouble>(const char* name, const Math::Vector3d& vector) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformVector<GLint>(const char* name, const Math::Vector3i& vector) const noexcept;

template void Graphics::Utils::ShaderProgram::setUniformVector<GLfloat>(const char* name, const Math::Vector4f& vector) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformVector<GLdouble>(const char* name, const Math::Vector4d& vector) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformVector<GLint>(const char* name, const Math::Vector4i& vector) const noexcept;

template void Graphics::Utils::ShaderProgram::setUniformMatrix<GLfloat>(const char* name, const Math::Matrix2x2f& matrix) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformMatrix<GLdouble>(const char* name, const Math::Matrix2x2d& matrix) const noexcept;

template void Graphics::Utils::ShaderProgram::setUniformMatrix<GLfloat>(const char* name, const Math::Matrix3x3f& matrix) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformMatrix<GLdouble>(const char* name, const Math::Matrix3x3d& matrix) const noexcept;

template void Graphics::Utils::ShaderProgram::setUniformMatrix<GLfloat>(const char* name, const Math::Matrix4x4f& matrix) const noexcept;
template void Graphics::Utils::ShaderProgram::setUniformMatrix<GLdouble>(const char* name, const Math::Matrix4x4d& matrix) const noexcept;
