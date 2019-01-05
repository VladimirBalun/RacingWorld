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
    std::array<wchar_t, Configuration::Game::MAX_SIZE_EMAIL> email;
    std::array<wchar_t, Configuration::Game::MAX_SIZE_PASSWORD> password;
    std::copy(Configuration::Player::PLAYER_EMAIL.begin(), Configuration::Player::PLAYER_EMAIL.end(), email.begin());
    std::copy(Configuration::Player::PLAYER_PASSWORD.begin(), Configuration::Player::PLAYER_PASSWORD.end(), password.begin());
    std::cout << (std::int8_t) email.size() << std::endl;

    // TODO: need to change on custom allocators
    std::unique_ptr<Login> packetToServer = std::make_unique<Login>(mPacketNumber++, email, (std::int8_t) email.size(), password, (std::int8_t) password.size());
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
    const Math::Vector3<float>& startPosition = Configuration::Player::PLAYER_START_POSITION;
    const Math::Vector3<float>& startDirection = Configuration::Player::PLAYER_START_DIRECTION;

    // TODO: need to change on custom allocators
    std::unique_ptr<InitializePosition> packetToServer = std::make_unique<InitializePosition>(mPacketNumber++, mCurrentToken, startPosition, startDirection);
    void* buffer = reinterpret_cast<void*>(packetToServer.get());
    mConnection.sendBuffer(buffer);

    // TODO: need to change on custom allocators
    std::unique_ptr<InitializePositionAnswer> packetFromServer = std::make_unique<InitializePositionAnswer>();
    return packetFromServer->mResultInitialization;
}
