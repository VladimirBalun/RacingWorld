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

#include "ShaderProgram.h"

Graphics::ShaderProgram::ShaderProgram(const std::string& vShaderFileName, const std::string& fShaderFileName) 
{
    const char* vShaderSourceCode = read_file(vShaderFileName).c_str();
    const char* fShaderSourceCode = read_file(fShaderFileName).c_str();
    const GLuint vertexShader = compileShader(vShaderSourceCode, GL_VERTEX_SHADER);
    const GLuint fragmantShader = compileShader(fShaderSourceCode, GL_FRAGMENT_SHADER);
    linkShaders(vertexShader, fragmantShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmantShader);
}

GLuint Graphics::ShaderProgram::compileShader(const char* shaderSourceCode, GLint shaderType)
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
        LOG_WARNING << "Shader was not compiled. Cause: " << errorLog << std::endl;
    }

    return shader;
}

GLvoid Graphics::ShaderProgram::linkShaders(GLuint vertexShader, GLuint fragmentShader)
{
    GLint isLinkedShaders;
    _program = glCreateProgram();
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &isLinkedShaders);

    if (!isLinkedShaders) 
    {
        GLchar errorLog[512];
        glGetProgramInfoLog(_program, 512, NULL, errorLog);
        LOG_WARNING << "Shaders were not linked. Cause: " << errorLog << std::endl;
    }
}

void Graphics::ShaderProgram::useShaderProgram() 
{
    glUseProgram(_program);
}
