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

#include "EPacketType.hpp"
#include "NetworkPacket.hpp"

#include "../../Math/Vector3.hpp"

namespace Platforms { namespace Network { namespace Protocol {

    #pragma pack(push, 1)

    class InitializePositionPacket : public NetworkPacket<InitializePositionPacket>, IPacketToServer
    {
    public:
        explicit InitializePositionPacket() : NetworkPacket(INITIALIZE_POSITION_PACKET) {}
        void setPacketNumber(std::int32_t number) noexcept;
        void setToken(std::int32_t token) noexcept;
        void setPosition(const Math::Vector3f position) noexcept;
        void setDirection(const Math::Vector3f direction) noexcept;
        char* toBuffer() noexcept;
    private:
        std::int32_t mToken;
        Math::Vector3f mPosition;
        Math::Vector3f mDirection;
    };

    #pragma pack(pop)

    inline void InitializePositionPacket::setPacketNumber(std::int32_t number) noexcept
    {
        mPacketNumber = number;
    }

    inline void InitializePositionPacket::setToken(std::int32_t token) noexcept
    {
        mToken = token;
    }

    inline void InitializePositionPacket::setPosition(const Math::Vector3f position) noexcept
    {
        mPosition = position;
    }

    inline void InitializePositionPacket::setDirection(const Math::Vector3f direction) noexcept
    {
        mDirection = direction;
    }

    inline char* InitializePositionPacket::toBuffer() noexcept
    {
        return reinterpret_cast<char*>(this);
    }

} } }
