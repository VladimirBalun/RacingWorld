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

#include "NetworkManager.hpp"

#include "Protocol/Protocol.hpp"
#include "../Utils/Debug.hpp"

Network::NetworkManager& Network::NetworkManager::getInstance() noexcept
{
    static NetworkManager instance{};
    return instance;
}

bool Network::NetworkManager::connect() noexcept
{
    m_is_connected = m_connection.connect();
    return m_is_connected;
}

bool Network::NetworkManager::login() noexcept
{
    try
    {
        Protocol::LoginPacket packet_to_server{};
        packet_to_server.setPacketNumber(m_packet_number++);
        packet_to_server.setEmailSize(static_cast<std::int16_t>(Configuration::Player::PLAYER_EMAIL.size()));
        packet_to_server.setPasswordSize(static_cast<std::int8_t>(Configuration::Player::PLAYER_PASSWORD.size()));
        packet_to_server.setEmail(Configuration::Player::PLAYER_EMAIL.data());
        packet_to_server.setPassword(Configuration::Player::PLAYER_PASSWORD.data());
        m_connection.write(packet_to_server.serialize(), sizeof(Protocol::LoginPacket));

        Protocol::LoginAnswerPacket packet_from_server{};
        m_connection.read(packet_from_server.serialize(), sizeof(Protocol::LoginAnswerPacket));
        m_current_token = packet_from_server.getToken();
        m_is_login = packet_from_server.getResultLogin();
        return m_is_login;
    }
    catch (const boost::system::system_error& error)
    {
        LOG_ERROR(error.what());
        return false;
    }
}

bool Network::NetworkManager::logout() noexcept
{
    try
    {
        Protocol::LogoutPacket packet_to_server{};
        packet_to_server.setPacketNumber(m_packet_number++);
        packet_to_server.setToken(m_current_token);
        m_connection.write(packet_to_server.serialize(), sizeof(Protocol::LogoutPacket));

        Protocol::LogoutAnswerPacket packet_from_server{};
        m_connection.read(packet_from_server.serialize(), sizeof(Protocol::LoginAnswerPacket));
        if (packet_from_server.getResultLogout())
        {
            m_is_login = false;
            m_is_connected = false;
        }
        return packet_from_server.getResultLogout();
    }
    catch (const boost::system::system_error& error)
    {
        LOG_ERROR(error.what());
        return false;
    }
}

bool Network::NetworkManager::isConnected() const noexcept
{
    return m_is_connected;
}

bool Network::NetworkManager::isLogin() const noexcept
{
    return m_is_login;
}
