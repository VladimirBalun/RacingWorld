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
    Memory::LinearAllocator shadersAllocator(ONE_VIRTUAL_PAGE);
    mShaderPrograms[BASE_SHADER] = createShader(shadersAllocator, "BaseShader.vert", "BaseShader.frag");
    mShaderPrograms[BASE_SHADER2] = createShader(shadersAllocator, "BaseShader2.vert", "BaseShader2.frag");
}

Graphics::Tools::ShaderProgram Graphics::Managers::ShaderManager::createShader(Memory::LinearAllocator& allocator, const char* vShaderName, const char* fShaderName) const noexcept
{
    const char* shadersPath = Configuration::getShadersPath();
    const std::size_t legthShadersPath = strlen(shadersPath);

    char* vertexShaderPath = Utils::createStringFromStrings(legthShadersPath + strlen(vShaderName) + 1,
        std::bind(&Memory::LinearAllocator::allocate, &allocator, std::placeholders::_1, std::placeholders::_2), shadersPath, vShaderName);
    char* fragmentShaderPath = Utils::createStringFromStrings(legthShadersPath + strlen(fShaderName) + 1,
        std::bind(&Memory::LinearAllocator::allocate, &allocator, std::placeholders::_1, std::placeholders::_2), shadersPath, fShaderName);

    return Tools::ShaderProgram(allocator, vertexShaderPath, fragmentShaderPath);
}

GLvoid Graphics::Managers::ShaderManager::useShaderProgram(EShaderType shaderType) const noexcept
{
    const Tools::ShaderProgram& shaderProgram = mShaderPrograms[shaderType];
    assert(shaderProgram.isInitialized() && "Incorrect type of shader program.");
    shaderProgram.use();
}

Graphics::Tools::ShaderProgram& Graphics::Managers::ShaderManager::getShader(EShaderType shaderType) noexcept
{
    return mShaderPrograms[shaderType];
}
