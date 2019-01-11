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
    // TODO: need to change on custom allocators
    std::unique_ptr<Login> packetToServer = std::make_unique<Login>();
    packetToServer->mType = LOGIN_PACKET;
    packetToServer->mNumber = mPacketNumber++;
    packetToServer->mEmailSize = Configuration::Player::PLAYER_EMAIL.size();
    packetToServer->mPasswordSize = Configuration::Player::PLAYER_PASSWORD.size();
    std::copy(Configuration::Player::PLAYER_EMAIL.begin(), Configuration::Player::PLAYER_EMAIL.end(), std::begin(packetToServer->mEmail));
    std::copy(Configuration::Player::PLAYER_PASSWORD.begin(), Configuration::Player::PLAYER_PASSWORD.end(), std::begin(packetToServer->mPassword));
    void* buffer = reinterpret_cast<void*>(packetToServer.get());
    mConnection.sendBuffer(buffer);

    // TODO: need to change on custom allocators
    std::unique_ptr<LoginAnswer> packetFromServer = std::make_unique<LoginAnswer>();
    mConnection.receiveBuffer(reinterpret_cast<void*>(packetFromServer.get()));
    mCurrentToken = packetFromServer->mToken;
    return packetFromServer->mResultLogin;
}

bool Platforms::Network::NetworkManager::initializePosition()
{
    // TODO: need to change on custom allocators
    std::unique_ptr<InitializePosition> packetToServer = std::make_unique<InitializePosition>();
    packetToServer->mType = INITIALIZE_POSITION_PACKET;
    packetToServer->mNumber = mPacketNumber++;
    packetToServer->mToken = mCurrentToken;
    packetToServer->mPosition = Configuration::Player::PLAYER_START_POSITION;
    packetToServer->mDirection = Configuration::Player::PLAYER_START_DIRECTION;
    void* buffer = reinterpret_cast<void*>(packetToServer.get());
    mConnection.sendBuffer(buffer);

    // TODO: need to change on custom allocators
    std::unique_ptr<InitializePositionAnswer> packetFromServer = std::make_unique<InitializePositionAnswer>();
    return packetFromServer->mResultInitialization;
}
