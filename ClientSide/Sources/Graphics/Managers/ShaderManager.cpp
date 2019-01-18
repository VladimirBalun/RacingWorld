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
#include "../../Utils/Logger.hpp"

void Graphics::Managers::ShaderManager::addShader(std::string key, const char* vShaderFileName, const char* fShaderFileName)
{
    auto res = shadersList.find(key);
    if (res != shadersList.end())
    {
        LOG_PRINT("This Shader Name already exists!");
    }
    else
    {
        Tools::ShaderProgram newShader(vShaderFileName, fShaderFileName);
        shadersList.emplace(std::make_pair(key, newShader.getProgram()));
    }
}

void Graphics::Managers::ShaderManager::setShader(std::string key)
{
    auto res = shadersList.find(key);
    if (res != shadersList.end())
    {
        currentShader = key;
        mProgram.setProgram(shadersList.at(currentShader));
    }
    else 
    {
        LOG_PRINT("This shader name does not exist!");
    }
}

void Graphics::Managers::ShaderManager::unsetShader()
{
    mProgram.unsetProgram();
}

UINT Graphics::Managers::ShaderManager::getIdShader(std::string key)
{
    if (currentShader != key) 
    {
        setShader(key);
    }

    auto res = shadersList.find(key);
    if (res != shadersList.end()) {
        return shadersList.at(key);
    }
    else 
    {
        LOG_PRINT("This Shader does not exist!");
    }
    return -1;
}

void Graphics::Managers::ShaderManager::destroyProgram(std::string key)
{
    UINT idProg = getIdShader(key);
    getShader(key).destroyProgram(idProg);
    shadersList.erase(key); 
}

Graphics::Tools::ShaderProgram Graphics::Managers::ShaderManager::getShader(std::string key)
{
    setShader(key);
    return mProgram;
}

void Graphics::Managers::ShaderManager::PrintShadersList()
{
    std::cout << "=========================================" << std::endl;
    std::cout << "List shaders" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    for (auto it = shadersList.begin(); it != shadersList.end(); ++it)
    {
        std::cout << (*it).first << " " << (*it).second << std::endl;
    }
    std::cout << "=========================================" << std::endl;
}
