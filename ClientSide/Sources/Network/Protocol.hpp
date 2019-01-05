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

#include <array>
#include <cstdint>

#include "../Math/Vector3.hpp"
#include "../System/MouseState.hpp"
#include "../System/KeyboardState.hpp"
#include "../Utils/Configuration.hpp"

namespace Platforms { namespace Network {

    enum PacketType
    {
        LOGIN_PACKET = 1,
        LOGIN_ANSWER_PACKET = 2,
        LOGOUT_PACKET = 3,
        LOGOUT_ANSWER_PACKET = 4,
        INITIALIZE_POSITION_PACKET = 5,
        INITIALIZE_POSITION_PACKET_ANSWER = 6,
        USER_ACTION_PACKET = 7,
        WORLD_ACTION_PACKET = 8
    };

    #pragma pack(push, 1)

    struct NetworkPacket 
    {
        std::int8_t mType = 0;
        std::int32_t mNumber = 0;

        NetworkPacket() = default;
        NetworkPacket(std::int32_t number, std::int8_t type)
            : mNumber(number), mType(type) {}
    };

    // Packet to server
    struct Login : public NetworkPacket
    {
        std::array<wchar_t, Configuration::Game::MAX_SIZE_EMAIL> mEmail;
        std::int8_t mEmailSize;
        std::array<wchar_t, Configuration::Game::MAX_SIZE_PASSWORD> mPassword;
        std::int8_t mPasswordSize;
        static constexpr std::uint16_t SIZE_PACKET = sizeof(mType) + sizeof(mNumber) + 
            sizeof(mEmail) + sizeof(mEmailSize) + sizeof(mPassword) + sizeof(mPasswordSize);

        Login() = default;
        Login(std::int32_t number, 
            const std::array<wchar_t, Configuration::Game::MAX_SIZE_EMAIL>& email,
            std::int8_t emailSize,
            const std::array<wchar_t, Configuration::Game::MAX_SIZE_PASSWORD>& password,
            std::int8_t passwordSize)
            : NetworkPacket(number, LOGIN_PACKET), mEmail(email), mEmailSize(emailSize), mPassword(password), mPasswordSize(passwordSize) {}
    };

    // Packet from server
    struct LoginAnswer : public NetworkPacket
    {
        std::int32_t mToken;
        bool mResultLogin;
        static constexpr std::uint16_t SIZE_PACKET = sizeof(mType) + sizeof(mNumber) + sizeof(mToken) + sizeof(mResultLogin);
    };

    // Packet to server
    struct InitializePosition : public NetworkPacket
    {
        const std::int32_t mToken;
        const Math::Vector3<float> mPosition;
        const Math::Vector3<float> mDirection;
        static constexpr std::uint16_t SIZE_PACKET = sizeof(mType) + sizeof(mNumber) + sizeof(mPosition) + sizeof(mDirection);

        InitializePosition() = default;
        InitializePosition(std::int32_t number, std::int32_t token, const Math::Vector3<float>& position, const Math::Vector3<float>& direction) 
            : NetworkPacket(number, INITIALIZE_POSITION_PACKET), mToken(token), mPosition(position), mDirection(direction) {}
    };

    // Packet from server
    struct InitializePositionAnswer : public NetworkPacket 
    {
        bool mResultInitialization;
        static constexpr std::uint8_t SIZE_PACKET = sizeof(mType) + sizeof(mNumber) + sizeof(mResultInitialization);
    };

    // Packet to server
    struct UserAction : public NetworkPacket
    {
        const std::int32_t token;
        const MouseState mouseState;
        const KeyboardState keyboardState;
        static constexpr std::uint16_t SIZE_PACKET = sizeof(mType) + sizeof(mNumber) + sizeof(token) + sizeof(mouseState) + sizeof(keyboardState);

        UserAction() = default;
        UserAction(std::int32_t number, std::int32_t token, const MouseState& mouseState, const KeyboardState& keyboardState)
            : NetworkPacket(number, USER_ACTION_PACKET), token(token), mouseState(mouseState), keyboardState(keyboardState) {}
    };

    // Packet from server
    struct WorldAction : public NetworkPacket
    {
        std::int32_t mToken;
        const Math::Vector3<float> mPositions[Configuration::Game::MAX_COUNT_PLAYERS];
        const Math::Vector3<float> mDirections[Configuration::Game::MAX_COUNT_PLAYERS];
        static constexpr std::uint16_t SIZE_PACKET = sizeof(mType) + sizeof(mNumber) + sizeof(mToken) + sizeof(mPositions) + sizeof(mDirections);
    };

    #pragma pack(pop)

}}
