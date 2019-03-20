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
    auto packetToServer = mPacketBuilder.createPacketToServer<Protocol::LoginPacket>();
    packetToServer->setPacketNumber(mPacketNumber++);
    packetToServer->setEmailSize(static_cast<std::int16_t>(Configuration::Player::PLAYER_EMAIL.size()));
    packetToServer->setPasswordSize(static_cast<std::int8_t>(Configuration::Player::PLAYER_PASSWORD.size()));
    packetToServer->setEmail(Configuration::Player::PLAYER_EMAIL.data());
    packetToServer->setPassword(Configuration::Player::PLAYER_PASSWORD.data());
    mConnection.sendBuffer(packetToServer->toBuffer(), sizeof(Protocol::LoginPacket));

    auto packetFromServer = mPacketBuilder.createPacketFromServer<Protocol::LoginAnswerPacket>();
    mConnection.receiveBuffer(packetFromServer->toBuffer());
    mCurrentToken = packetFromServer->getToken();
    return packetFromServer->getResultLogin();
}
