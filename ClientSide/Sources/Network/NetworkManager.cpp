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
    const wchar_t* email = Configuration::Player::PLAYER_EMAIL;
    const wchar_t* password = Configuration::Player::PLAYER_PASSWORD;
    
    //Login* loginPacket(mPacketNumber, email, password);
    //void* buffer = reinterpret_cast<void*>(loginPacket);
    //mConnection.sendBuffer(buffer);
    return true;
}

bool Platforms::Network::NetworkManager::initializePosition(const Math::Vector3<float>& position, const Math::Vector3<float>& direction)
{
    return true;
}
