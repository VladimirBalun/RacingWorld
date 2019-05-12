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

#include "ShaderManager.hpp"

GLvoid Graphics::Managers::ShaderManager::initializeShaders() noexcept
{
    mShaderPrograms[BASE_SHADER] = createShader("/BaseShader.vert", "/BaseShader.frag");
    mShaderPrograms[FONT_SHADER] = createShader("/FontShader.vert", "/FontShader.frag");
}

Graphics::Tools::ShaderProgram Graphics::Managers::ShaderManager::createShader(const char* vShaderName, const char* fShaderName) const noexcept
{
    std::string vShaderFullPath(Configuration::getShadersPath());
    std::string fShaderFullPath(Configuration::getShadersPath());
    vShaderFullPath.append(vShaderName);
    fShaderFullPath.append(fShaderName);
    return Tools::ShaderProgram(vShaderFullPath, fShaderFullPath);
}

GLvoid Graphics::Managers::ShaderManager::useShaderProgram(EShaderType shaderType) const noexcept
{
    const Tools::ShaderProgram& shaderProgram = mShaderPrograms[shaderType];
    ASSERT(shaderProgram.isInitialized(), "Incorrect type of shader program.");
    shaderProgram.use();
}

Graphics::Tools::ShaderProgram& Graphics::Managers::ShaderManager::getShader(EShaderType shaderType) noexcept
{
    return mShaderPrograms[shaderType];
}

Graphics::Managers::ShaderManager::~ShaderManager()
{
    for (GLubyte i = 0; i < COUNT_SHADER_TYPES; i++)
        mShaderPrograms[i].destroy();
}
