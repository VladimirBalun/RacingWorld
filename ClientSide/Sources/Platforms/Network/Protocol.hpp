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

namespace Platforms { namespace Network {

enum PacketType 
{
    PLAYER_LOCATION_PACKET
};

#pragma pack(0)
struct NetworkPacket 
{
    std::int8_t type;
    std::int32_t number;

    NetworkPacket() = default;
    NetworkPacket(std::int32_t number, std::int8_t type)
        : number(number), type(type) {}
};

#pragma pack(0)
struct PlayerLocationPacket : public NetworkPacket 
{
    float x_pox, y_pos, z_pos; // position
    float x_dir, y_dir, z_dir; // direction
    static constexpr int SIZE_PACKET = sizeof(std::int32_t) * (sizeof(float) * 6);

    PlayerLocationPacket() = default;
    PlayerLocationPacket(std::int32_t number, float x_pox, float y_pos, float z_pos, float x_dir, float y_dir, float z_dir)
        : NetworkPacket(number, PLAYER_LOCATION_PACKET), x_pox(x_pox), y_pos(y_pos), z_pos(z_pos), x_dir(x_dir), y_dir(y_dir), z_dir(z_dir) {}
};

} }
