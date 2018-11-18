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

#include "UDPConnection.h"

Platforms::Network::UDPConnection::UDPConnection(LPCSTR ipAddress, std::uint16_t port)
{
    WSADATA socketData;
    if (WSAStartup(MAKEWORD(2, 2), &socketData) != 0)
    {
        LOG_ERROR << "Socket was not initialized. Cause: " << WSAGetLastError() << std::endl;
        throw Exceptions::NetworkException("Socket was not initialized");
    }

    if ((_socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        LOG_ERROR << "Socket was not created. Cause: " << WSAGetLastError() << std::endl;
        throw Exceptions::NetworkException("Socket was not created");
    }

    memset((CHAR*) &_socketAddress, 0, sizeof(_socketAddress));
    _socketAddress.sin_family = AF_INET;
    _socketAddress.sin_port = htons(port);
    _socketAddress.sin_addr.S_un.S_addr = inet_addr(ipAddress);
}

VOID Platforms::Network::UDPConnection::sendBuffer(const std::array<CHAR, 512>& buffer) noexcept
{
    sendto(_socketHandle, buffer.data(), 512, 0, (struct sockaddr*) &_socketAddress, 512);
}

VOID Platforms::Network::UDPConnection::receiveBuffer(std::array<CHAR, 512>& buffer) noexcept
{
    INT sizeStub = 0;
    recvfrom(_socketHandle, buffer.data(), 512, 0, (struct sockaddr*) &_socketAddress, &sizeStub);
}

Platforms::Network::UDPConnection::~UDPConnection()
{
    closesocket(_socketHandle);
    WSACleanup();
}
