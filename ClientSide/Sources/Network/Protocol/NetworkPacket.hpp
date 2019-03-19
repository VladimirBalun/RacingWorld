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

#include <cstdint>

#include "../Endianness/BigEndian.hpp"

namespace Network { namespace Protocol {

    // Interfaces
    struct IPacketToServer {};
    struct IPacketFromServer {};

    #pragma pack(push, 1)

    // Abstract class
    template<typename DerivedType>
    class NetworkPacket
    {
    public:
        explicit NetworkPacket() noexcept = default;
        explicit NetworkPacket(std::uint8_t type) noexcept : mPacketType(type) {}
        char* toBuffer() noexcept;
    protected:
        Endianness::int8be_t mPacketType = 0;
        Endianness::int32be_t mPacketNumber = 0;
    };

    #pragma pack(pop)

    template<typename DerivedType>
    char* NetworkPacket<DerivedType>::toBuffer() noexcept
    {
        return static_cast<DerivedType*>(this)->toBuffer();
    }

} }
