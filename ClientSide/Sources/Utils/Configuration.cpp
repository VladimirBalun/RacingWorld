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

const char* Configuration::Network::SERVER_ADDRESS = "127.0.0.1";

const std::string Configuration::Player::PLAYER_EMAIL = u8"player@gmail.com";
const std::string Configuration::Player::PLAYER_PASSWORD = u8"difficult_password";

const char* Configuration::getShadersPath() noexcept
{
    static char path[MAX_PATH] = { 0 };
    if (!*path) 
    {
        GetCurrentDirectory(MAX_PATH, path);
        Utils::getParentPathFromString(path);
        Utils::concatenateStringsToString(path, MAX_PATH, "\\Resources", "\\Shaders\\");
    }
    return path;
}

const char* Configuration::getTexturesPath() noexcept
{
    static char path[MAX_PATH] = { 0 };
    if (!*path)
    {
        GetCurrentDirectory(MAX_PATH, path);
        Utils::getParentPathFromString(path);
        Utils::concatenateStringsToString(path, MAX_PATH, "\\Resources", "\\Textures\\");
    }
    return path;
}

const char* Configuration::getModelsPath() noexcept
{
    static char path[MAX_PATH] = { 0 };
    if (!*path)
    {
        GetCurrentDirectory(MAX_PATH, path);
        Utils::getParentPathFromString(path);
        Utils::concatenateStringsToString(path, MAX_PATH, "\\Resources", "\\Models\\");
    }
    return path;
}
