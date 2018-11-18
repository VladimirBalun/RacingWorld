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
    double x_pos, y_pos, z_pos; // position
    double x_dir, y_dir, z_dir; // direction
    static constexpr int SIZE_PACKET = sizeof(type) + sizeof(number) +
        sizeof(x_pos) + sizeof(y_pos) + sizeof(z_pos) + sizeof(x_dir) + sizeof(y_dir) + sizeof(z_dir);

    PlayerLocationPacket() = default;
    PlayerLocationPacket(std::int32_t number, double x_pos, double y_pos, double z_pos, double x_dir, double y_dir, double z_dir)
        : NetworkPacket(number, PLAYER_LOCATION_PACKET), x_pos(x_pos), y_pos(y_pos), z_pos(z_pos), x_dir(x_dir), y_dir(y_dir), z_dir(z_dir) {}
};

} }
