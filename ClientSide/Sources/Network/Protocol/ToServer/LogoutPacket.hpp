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

#include "../NetworkPacket.hpp"
#include "../../Endianness/BigEndian.hpp"

namespace Network { namespace Protocol {

    #pragma pack(push, 1)

    class LogoutPacket : NetworkPacket<LogoutPacket>, public IPacketToServer
    {
    public:
        LogoutPacket() noexcept
            : NetworkPacket(static_cast<std::uint8_t>(PacketType::LOGOUT_PACKET)) {}
        void setPacketNumber(std::int32_t number) noexcept;
        void setToken(std::int32_t token) noexcept;
        char* serialize() noexcept;
    private:
        Endianness::int32be_t m_token = 0;
    };

    #pragma pack(pop)

    inline void LogoutPacket::setPacketNumber(const std::int32_t number) noexcept
    {
        m_packet_number = number;
    }

    inline void LogoutPacket::setToken(const std::int32_t token) noexcept
    {
        m_token = token;
    }

    inline char* LogoutPacket::serialize() noexcept
    {
        return reinterpret_cast<char*>(this);
    }

}}
