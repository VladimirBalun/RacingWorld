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

#include "Configuration.hpp"

std::uint16_t Configuration::Window::windowWidth = 800;
std::uint16_t Configuration::Window::windowHeight = 600;

const String Configuration::Network::SERVER_ADDRESS("127.0.0.1");

const String Configuration::Player::PLAYER_EMAIL("player@gmail.com");
const String Configuration::Player::PLAYER_PASSWORD("difficult_password");

const String& Configuration::getShadersPath() noexcept
{
    static String shadersPath{};
    if (shadersPath.isEmpty())
    {
        char buffer[MAX_PATH] = { NULL };
        GetCurrentDirectory(MAX_PATH, buffer);
        shadersPath = getParentPath(buffer);
        shadersPath.append("\\Resources");
        shadersPath.append("\\Shaders\\");
    }
    return shadersPath;
}

const String& Configuration::getTexturesPath() noexcept
{
    static String texturesPath{};
    if (texturesPath.isEmpty())
    {
        char buffer[MAX_PATH] = { NULL };
        GetCurrentDirectory(MAX_PATH, buffer);
        texturesPath = getParentPath(buffer);
        texturesPath.append("\\Resources");
        texturesPath.append("\\Textures\\");
    }
    return texturesPath;
}

const String& Configuration::getModelsPath() noexcept
{
    static String modelsPath{};
    if (modelsPath.isEmpty())
    {
        char buffer[MAX_PATH] = { NULL };
        GetCurrentDirectory(MAX_PATH, buffer);
        modelsPath = getParentPath(buffer);
        modelsPath.append("\\Resources");
        modelsPath.append("\\Models\\");
    }
    return modelsPath;
}
