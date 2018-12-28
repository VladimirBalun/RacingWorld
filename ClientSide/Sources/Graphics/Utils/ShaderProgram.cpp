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

Graphics::Utils::ShaderProgram::ShaderProgram(const std::string& vShaderFileName, const std::string& fShaderFileName)
{
    const char* vShaderSourceCode = read_file(vShaderFileName).c_str();
    const char* fShaderSourceCode = read_file(fShaderFileName).c_str();
    const GLuint vertexShader = compileShader(vShaderSourceCode, GL_VERTEX_SHADER);
    const GLuint fragmantShader = compileShader(fShaderSourceCode, GL_FRAGMENT_SHADER);
    linkShaders(vertexShader, fragmantShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmantShader);
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

void Graphics::Utils::ShaderProgram::useShaderProgram()
{
    glUseProgram(mProgram);
}
