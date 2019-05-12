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

#include <string>
#include <filesystem>

#include "../Math/Vectors/Vector3.hpp"

struct Configuration 
{

    struct Window 
    {
        static std::uint16_t window_width;
        static std::uint16_t window_height;
    };

    struct Game
    {
        static const std::uint8_t MAX_COUNT_PLAYERS = 10;
        static const std::uint8_t MAX_SIZE_EMAIL = 254;
        static const std::uint8_t MAX_SIZE_PASSWORD = 32;
    };

    struct Player 
    {
        static const std::string PLAYER_EMAIL;
        static const std::string PLAYER_PASSWORD;
    };

    struct Network 
    {
        static const std::string SERVER_ADDRESS;
        static const std::uint16_t SERVER_PORT = 17017;
    };

    static std::string_view getShadersPath() noexcept;
    static std::string_view getModelsPath() noexcept;

};
