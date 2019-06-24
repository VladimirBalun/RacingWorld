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

#include <unordered_map>

#include "../Tools/ShaderProgram.hpp"

#define g_shader_manager Graphics::Managers::ShaderManager::getInstance()

namespace Graphics { namespace Managers {

    // Singleton
    class ShaderManager
    {
    public:
        static ShaderManager& getInstance() noexcept;
        GLvoid initializeShaders() noexcept;
        GLboolean isExistShader(const std::string& shader_name) const noexcept;
        Tools::ShaderProgram* getShader(const std::string& shader_name) noexcept;
        ~ShaderManager();
    private:
        ShaderManager() noexcept = default;
        explicit ShaderManager(const ShaderManager& other) noexcept = delete;
        ShaderManager& operator = (const ShaderManager& other) noexcept = delete;
    private:
        std::unordered_map<std::string, Tools::ShaderProgram> m_shader_programs{};
    };

} }
