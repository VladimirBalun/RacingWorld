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

#include "../Tools/ShaderProgram.hpp"
#include "../../Utils/Debug.hpp"
#include "../../Utils/Configuration.hpp"

namespace Graphics { namespace Managers {

    enum EShaderType 
    {
        BASE_SHADER,
        FONT_SHADER,
        COUNT_SHADER_TYPES // Used for setting size of shaders array 
    };

    class ShaderManager
    {
    public:
        GLvoid initializeShaders() noexcept;
        GLvoid useShaderProgram(EShaderType shaderType) const noexcept;
        Tools::ShaderProgram& getShader(EShaderType shaderType) noexcept;
        ~ShaderManager();
    private: 
        Tools::ShaderProgram createShader(const char* vShaderPath, const char* fShaderPath) const noexcept;
    private:
        Tools::ShaderProgram mShaderPrograms[COUNT_SHADER_TYPES];
    };

} }
