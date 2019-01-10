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
   const char* vShaderSourceCode = strdup(readFile(vShaderFileName).c_str());
   const char* fShaderSourceCode = strdup(readFile(fShaderFileName).c_str());

    const GLuint vertexShader = _compileShader(vShaderSourceCode, GL_VERTEX_SHADER);
    const GLuint fragmantShader = _compileShader(fShaderSourceCode, GL_FRAGMENT_SHADER);
    _linkShaders(vertexShader, fragmantShader);
    glDetachShader(mProgram, vertexShader);
    glDetachShader(mProgram, fragmantShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmantShader);
}

GLuint Graphics::Utils::ShaderProgram::_compileShader(const char* shaderSourceCode, GLint shaderType)
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

GLvoid Graphics::Utils::ShaderProgram::_linkShaders(GLuint vertexShader, GLuint fragmentShader)
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

//////////////////////////////////////////////////////////////////////////////
void Graphics::Utils::ShaderProgram::destroyProgram()
{
    glDeleteProgram(mProgram);
}

void Graphics::Utils::ShaderProgram::destroyProgramID(unsigned int idProgram)
{
    glDeleteProgram(idProgram);
}

Graphics::Utils::ShaderProgram::~ShaderProgram()
{
    destroyProgram();
}

//////////////////////////////////////////////////////////////////////////////
void Graphics::Utils::ShaderProgram::setProgram()
{
    glUseProgram(mProgram);
}

void Graphics::Utils::ShaderProgram::unsetProgram()
{
    glUseProgram(NULL);
}

GLuint Graphics::Utils::ShaderProgram::getProgram()
{
    return mProgram;
}

//////////////////////////////////////////////////////////////////////////////
GLuint Graphics::Utils::ShaderProgram::getAttribLocation(const char* name)
{
    return glGetAttribLocation(mProgram, name);
}

GLuint Graphics::Utils::ShaderProgram::getUniformLocation(const char* name) const
{
    return glGetUniformLocation(mProgram, name);
}

//////////////////////////////////////////////////////////////////////////////
void Graphics::Utils::ShaderProgram::setInt(const char * name, int value) const
{
    glUniform1i(getUniformLocation(name), value);
}

void Graphics::Utils::ShaderProgram::setBool(const char * name, bool value) const
{
    glUniform1i(getUniformLocation(name), (int)value);
}

void Graphics::Utils::ShaderProgram::setFloat(const char * name, float value) const
{
    glUniform1f(getUniformLocation(name), value);
}

void Graphics::Utils::ShaderProgram::setVector2(const char * name, float v0, float v1) const
{
    glUniform2f(getUniformLocation(name), v0, v1);
}

void Graphics::Utils::ShaderProgram::setVector3(const char * name, float v0, float v1, float v2) const
{
    glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void Graphics::Utils::ShaderProgram::setVector4(const char * name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

//////////////////////////////////////////////////////////////////////////////
void Graphics::Utils::ShaderProgram::setVector2(const char * name, const Math::Vector2<float> &value) const
{
    //glUniform2fv(getUniformLocation(name), 1, value);
    glUniform2f(getUniformLocation(name), value.getX() , value.getY());
}

void Graphics::Utils::ShaderProgram::setVector3(const char * name, const Math::Vector3<float> &value) const
{
    //glUniform3fv(getUniformLocation(name), 1, value);
    glUniform3f(getUniformLocation(name), value.getX(), value.getY(), value.getZ());
}

void Graphics::Utils::ShaderProgram::setVector4(const char * name, const Math::Vector4<float> &value) const
{
    //glUniform4fv(getUniformLocation(name), 1, &value[0]);
    glUniform4f(getUniformLocation(name), value.getX(), value.getY(), value.getZ(), value.getW());
}

//////////////////////////////////////////////////////////////////////////////
void Graphics::Utils::ShaderProgram::setMatrix2(const char * name, const Math::Matrix2x2<float> &value) const
{
    //std::array<float, 4> array;
    //value.toArray(array);
    //glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, array);
}

void Graphics::Utils::ShaderProgram::setMatrix3(const char * name, const Math::Matrix3x3<float> &value) const
{
    //glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Graphics::Utils::ShaderProgram::setMatrix4(const char * name, const Math::Matrix4x4<float> &value) const
{
    //glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value);
}
