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

#include "../EPacketType.hpp"
#include "../NetworkPacket.hpp"
#include "../../Endianness/BigEndian.hpp"

namespace Network { namespace Protocol {

    #pragma pack(push, 1)

    class LoginAnswerPacket : NetworkPacket<LoginAnswerPacket>, public IPacketFromServer
    {
    public:
        explicit LoginAnswerPacket() noexcept = default;
        std::int32_t getPacketNumber() const noexcept;
        std::int32_t getToken() const noexcept;
        bool getResultLogin() const noexcept;
        char* toBuffer() noexcept;
    private:
        Endianness::int32be_t m_token;
        bool m_result_login;
    };

    #pragma pack(pop)

    inline std::int32_t LoginAnswerPacket::getPacketNumber() const noexcept
    {
        return m_packet_number;
    }

    inline std::int32_t LoginAnswerPacket::getToken() const noexcept
    {
        return m_token;
    }

    inline bool LoginAnswerPacket::getResultLogin() const noexcept
    {
        return m_result_login;
    }
    
    inline char* LoginAnswerPacket::toBuffer() noexcept
    {
        return reinterpret_cast<char*>(this);
    }

} }
