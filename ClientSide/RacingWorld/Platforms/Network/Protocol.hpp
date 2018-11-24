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

#include <cstdint>

#include "../MouseState.h"
#include "../KeyboardState.h"

namespace Platforms { namespace Network {

    enum PacketType 
    {
        PLAYER_STATE_PACKET,
        PLAYER_LOCATION_PACKET
    };

    #pragma pack(1)
    struct NetworkPacket 
    {
        const std::int8_t type;
        const std::int32_t number;
        static constexpr std::uint8_t SIZE_BASE_PACKET = sizeof(type) + sizeof(number);

        NetworkPacket() = default;
        NetworkPacket(std::int32_t number, std::int8_t type)
            : number(number), type(type) {}
    };

    #pragma pack(1)
    struct PlayerStatePacket : public NetworkPacket
    {
        const MouseState mouseState;
        const KeyboardState keyboardState;
        static constexpr std::uint8_t SIZE_PLAYER_STATE_PACKET = SIZE_BASE_PACKET 
            + sizeof(mouseState) + sizeof(keyboardState);

        PlayerStatePacket() = default;
        PlayerStatePacket(std::int32_t number, const MouseState& mouseState, const KeyboardState& keyboardState)
            : NetworkPacket(number, PLAYER_LOCATION_PACKET), mouseState(mouseState), keyboardState(keyboardState) {}
    };


    #pragma pack(1)
    struct PlayerLocationPacket : public NetworkPacket 
    {
        const float direction;
        const float x_pos, y_pos, z_pos;
        static constexpr std::uint8_t SIZE_PLAYER_LOCATION_PACKET = SIZE_BASE_PACKET +
            sizeof(x_pos) + sizeof(y_pos) + sizeof(z_pos) + sizeof(direction);

        PlayerLocationPacket() = default;
        PlayerLocationPacket(std::int32_t number, float x_pos, float y_pos, float z_pos, float direction)
            : NetworkPacket(number, PLAYER_LOCATION_PACKET), x_pos(x_pos), y_pos(y_pos), z_pos(z_pos), direction(direction) {}
    };

} }
