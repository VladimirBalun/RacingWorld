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

#pragma once

#include <map>

#include "../Tools/ShaderProgram.hpp"

namespace Graphics { namespace Managers {
    
    class ShaderManager
    {
    public:
        void addShader(std::string key, const char* vShaderFileName, const char* fShaderFileName);
        void setShader(std::string key);
        void unsetShader();
        UINT getIdShader(std::string key);
        void destroyProgram(std::string key);
        Tools::ShaderProgram getShader(std::string key);
        void PrintShadersList(); // for debugging
    private:
        std::string currentShader;
        std::map<std::string, UINT> shadersList;
        Tools::ShaderProgram mProgram;
    };

} }

