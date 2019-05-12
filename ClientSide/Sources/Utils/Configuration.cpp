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

std::uint16_t Configuration::Window::window_width = 800;
std::uint16_t Configuration::Window::window_height = 600;

const std::string Configuration::Network::SERVER_ADDRESS("127.0.0.1");

const std::string Configuration::Player::PLAYER_EMAIL("player@gmail.com");
const std::string Configuration::Player::PLAYER_PASSWORD("difficult_password");

std::string_view Configuration::getShadersPath() noexcept
{
    static const std::string shaders_path = (std::filesystem::current_path().parent_path() / "Resources" / "Shaders").string();
    return shaders_path;
}

std::string_view Configuration::getModelsPath() noexcept
{
    static const std::string models_path = (std::filesystem::current_path().parent_path() / "Resources" / "Models").string();
    return models_path;
}
