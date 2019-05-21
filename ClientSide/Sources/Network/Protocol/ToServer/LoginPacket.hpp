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
#include "../../../Utils/Configuration.hpp"

namespace Network { namespace Protocol {

    #pragma pack(push, 1)

    class LoginPacket : NetworkPacket<LoginPacket>, public IPacketToServer
    {
    public:
        LoginPacket() noexcept
            : NetworkPacket(static_cast<std::uint8_t>(PacketType::LOGIN_PACKET)) {}
        void setEmail(const char* email) noexcept;
        void setPassword(const char* password) noexcept;
        void setPacketNumber(std::int32_t number) noexcept;
        void setEmailSize(std::int16_t email_size) noexcept;
        void setPasswordSize(std::int8_t password_size) noexcept;
        char* serialize() noexcept;
    private:
        char m_email[Configuration::Game::MAX_SIZE_EMAIL] = { 0 };
        Endianness::int16be_t m_email_size = 0;
        char m_password[Configuration::Game::MAX_SIZE_PASSWORD] = { 0 };
        Endianness::int8be_t m_password_size = 0;
    };

    #pragma pack(pop)

    inline void LoginPacket::setEmail(const char* email) noexcept
    {
        for (std::uint16_t i = 0; i < Configuration::Game::MAX_SIZE_EMAIL; i++)
            m_email[i] = email[i];
    }

    inline void LoginPacket::setPassword(const char* password) noexcept
    {
        for (std::uint8_t i = 0; i < Configuration::Game::MAX_SIZE_PASSWORD; i++)
            m_password[i] = password[i];
    }

    inline void LoginPacket::setPacketNumber(const std::int32_t number) noexcept
    {
        m_packet_number = number;
    }

    inline void LoginPacket::setEmailSize(const std::int16_t email_size) noexcept
    {
        m_email_size = email_size;
    }

    inline void LoginPacket::setPasswordSize(const std::int8_t password_size) noexcept
    {
        m_password_size = password_size;
    }

    inline char* LoginPacket::serialize() noexcept
    {
        return reinterpret_cast<char*>(this);
    }

}}
