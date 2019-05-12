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

bool Network::NetworkManager::login() noexcept
{
    Protocol::LoginPacket packet_to_server{};
    packet_to_server.setPacketNumber(m_packet_number++);
    packet_to_server.setEmailSize(static_cast<std::int16_t>(Configuration::Player::PLAYER_EMAIL.size()));
    packet_to_server.setPasswordSize(static_cast<std::int8_t>(Configuration::Player::PLAYER_PASSWORD.size()));
    packet_to_server.setEmail(Configuration::Player::PLAYER_EMAIL.data());
    packet_to_server.setPassword(Configuration::Player::PLAYER_PASSWORD.data());
    m_connection.sendBuffer(packet_to_server.toBuffer(), sizeof(Protocol::LoginPacket));

    Protocol::LoginAnswerPacket packet_from_server{};
    m_connection.receiveBuffer(packet_from_server.toBuffer());
    m_current_token = packet_from_server.getToken();
    return packet_from_server.getResultLogin();
}
