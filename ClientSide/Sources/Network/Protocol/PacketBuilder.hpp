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

#include <type_traits>

#include "Protocol.hpp"
#include "../../Memory/LinearAllocator.hpp"

namespace Network { namespace Protocol {

    class PacketBuilder 
    {
    public:
        explicit PacketBuilder()
            : mPacketsToServerAllocator(ONE_VIRTUAL_PAGE), mPacketsFromServerAllocator(ONE_VIRTUAL_PAGE) {}
        template<typename PacketType>
        PacketType* createPacketToServer() noexcept;
        template<typename PacketType>
        PacketType* createPacketFromServer() noexcept;
    private:
        Memory::LinearAllocator mPacketsToServerAllocator;
        Memory::LinearAllocator mPacketsFromServerAllocator;
    };

    template<typename PacketType>
    PacketType* PacketBuilder::createPacketToServer() noexcept
    {
        // static_assert(std::is_base_of<IPacketToServer, PacketType>::value, "Incorrect packet to server type.");
        void* memoryForPacket = mPacketsToServerAllocator.allocate(sizeof(PacketType), sizeof(PacketType));
        PacketType* packet = new (memoryForPacket) PacketType();
        return packet;
    }

    template<typename PacketType>
    PacketType* PacketBuilder::createPacketFromServer() noexcept
    {
        // static_assert(std::is_base_of<IPacketFromServer, PacketType>::value, "Incorrect packet from server type.");
        void* memoryForPacket = mPacketsToServerAllocator.allocate(sizeof(PacketType), sizeof(PacketType));
        PacketType* packet = new (memoryForPacket) PacketType();
        return packet;
    }

} }
