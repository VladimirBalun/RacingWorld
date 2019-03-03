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
#include <cstdlib>
#include <Winsock2.h>
#include <WS2tcpip.h>

#include "../Utils/Debug.hpp"

namespace Network {

    class UDPConnection 
    {
    public:
        explicit UDPConnection(LPCSTR ipAddress, std::uint16_t port);
        void sendBuffer(char* buffer, std::size_t size) noexcept;
        void receiveBuffer(char* buffer) noexcept;
        ~UDPConnection();
    private:
        int mSocketHandle;
        struct sockaddr_in mSocketAddress;
        static const std::uint16_t MAX_PACKET_SIZE = 1024;
    };

}
