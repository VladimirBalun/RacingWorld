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

namespace Network { namespace Protocol {

    #pragma pack(push, 1)

    class LogoutAnswerPacket : NetworkPacket<LogoutAnswerPacket>, public IPacketFromServer
    {
    public:
        std::int32_t getPacketNumber() const noexcept;
        bool getResultLogout() const noexcept;
        char* serialize() noexcept;
    private:
        bool m_result_logout = false;
    };

    #pragma pack(pop)

    inline std::int32_t LogoutAnswerPacket::getPacketNumber() const noexcept
    {
        return m_packet_number;
    }

    inline bool LogoutAnswerPacket::getResultLogout() const noexcept
    {
        return m_result_logout;
    }

    inline char* LogoutAnswerPacket::serialize() noexcept
    {
        return reinterpret_cast<char*>(this);
    }

}}
