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

bool Platforms::Network::NetworkManager::login() 
{
    wchar_t email[Configuration::Game::MAX_SIZE_EMAIL];
    wchar_t password[Configuration::Game::MAX_SIZE_PASSWORD];
    std::copy(Configuration::Player::PLAYER_EMAIL.begin(), Configuration::Player::PLAYER_EMAIL.end(), std::begin(email));
    std::copy(Configuration::Player::PLAYER_PASSWORD.begin(), Configuration::Player::PLAYER_PASSWORD.end(), std::begin(password));

    // TODO: need to change on custom allocators
    std::unique_ptr<Protocol::LoginPacket> packetToServer = std::make_unique<Protocol::LoginPacket>();
    packetToServer->setPacketNumber(mPacketNumber++);
    packetToServer->setEmailSize((std::int16_t) Configuration::Player::PLAYER_EMAIL.size());
    packetToServer->setPasswordSize((std::int16_t) Configuration::Player::PLAYER_PASSWORD.size());
    packetToServer->setEmail(email);
    packetToServer->setPassword(password);
    mConnection.sendBuffer(packetToServer->toBuffer());

    // TODO: need to change on custom allocators
    std::unique_ptr<Protocol::LoginAnswerPacket> packetFromServer = std::make_unique<Protocol::LoginAnswerPacket>();
    mConnection.receiveBuffer(packetFromServer->toBuffer());
    mCurrentToken = packetFromServer->getToken();
    return packetFromServer->getResultLogin();
}

bool Platforms::Network::NetworkManager::initializePosition()
{
    // TODO: need to change on custom allocators
    std::unique_ptr<Protocol::InitializePositionPacket> packetToServer = std::make_unique<Protocol::InitializePositionPacket>();
    packetToServer->setPacketNumber(mPacketNumber++);
    packetToServer->setToken(mCurrentToken);
    packetToServer->setPosition({10.f, 2.0f, 3.0f});//Configuration::Player::PLAYER_START_POSITION);
    packetToServer->setDirection(Configuration::Player::PLAYER_START_DIRECTION);
    mConnection.sendBuffer(packetToServer->toBuffer());

    // TODO: need to change on custom allocators
    std::unique_ptr<Protocol::InitializePositionAnswerPacket> packetFromServer = std::make_unique<Protocol::InitializePositionAnswerPacket>();
    mConnection.receiveBuffer(packetFromServer->toBuffer());
    return packetFromServer->getResultInitialization();
}
