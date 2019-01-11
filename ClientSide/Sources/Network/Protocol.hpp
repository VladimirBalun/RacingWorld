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

#include "../Math/Vector3.hpp"
#include "../System/MouseState.hpp"
#include "../System/KeyboardState.hpp"
#include "../Utils/Configuration.hpp"

namespace Platforms { namespace Network {

    enum PacketType
    {
        ERROR_PACKET = 0,
        LOGIN_PACKET = 1,
        LOGIN_ANSWER_PACKET = 2,
        LOGOUT_PACKET = 3,
        LOGOUT_ANSWER_PACKET = 4,
        INITIALIZE_POSITION_PACKET = 5,
        INITIALIZE_POSITION_PACKET_ANSWER = 6,
        USER_ACTION_PACKET = 7,
        WORLD_ACTION_PACKET = 8
    };

    // Interfaces
    struct IPacketFromServer {};
    struct IPacketToServer {};

    #pragma pack(push, 1)

    struct NetworkPacket 
    {
        std::int8_t mType = 0;
        std::int32_t mNumber = 0;
    };

    struct Login : public NetworkPacket, IPacketToServer
    {
        wchar_t mEmail[Configuration::Game::MAX_SIZE_EMAIL];
        std::int8_t mEmailSize;
        wchar_t mPassword[Configuration::Game::MAX_SIZE_PASSWORD];
        std::int8_t mPasswordSize;
    };

    struct LoginAnswer : public NetworkPacket, IPacketFromServer
    {
        std::int32_t mToken;
        bool mResultLogin;
    };

    struct InitializePosition : public NetworkPacket, IPacketToServer
    {
        std::int32_t mToken;
        Math::Vector3f mPosition;
        Math::Vector3f mDirection;
    };

    struct InitializePositionAnswer : public NetworkPacket, IPacketFromServer
    {
        bool mResultInitialization;
    };

    struct UserAction : public NetworkPacket, IPacketToServer
    {
        std::int32_t token;
        MouseState mouseState;
        KeyboardState keyboardState;
    };

    struct WorldAction : public NetworkPacket, IPacketFromServer
    {
        std::int32_t mToken;
        Math::Vector3f mPositions[Configuration::Game::MAX_COUNT_PLAYERS];
        Math::Vector3f mDirections[Configuration::Game::MAX_COUNT_PLAYERS];
    };

    #pragma pack(pop)

}}
