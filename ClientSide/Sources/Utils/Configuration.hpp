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

#include "../Math/Vector3.hpp"

struct Configuration 
{
    struct Game
    {
        static const std::uint8_t MAX_COUNT_PLAYERS = 10;
        static const std::uint8_t MAX_SIZE_EMAIL = 254;
        static const std::uint8_t MAX_SIZE_PASSWORD = 32;
    };

    struct Player 
    {
        static const std::wstring PLAYER_EMAIL;
        static const std::wstring PLAYER_PASSWORD;
        static const Math::Vector3<float> PLAYER_START_POSITION;
        static const Math::Vector3<float> PLAYER_START_DIRECTION;
    };

    struct Network 
    {
        static const char* SERVER_ADDRESS;
        static const std::uint16_t SERVER_PORT = 17012;
    };
};
