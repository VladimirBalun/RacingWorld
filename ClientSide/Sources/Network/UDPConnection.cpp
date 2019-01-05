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

#include "UDPConnection.hpp"

Platforms::Network::UDPConnection::UDPConnection(LPCSTR ipAddress, std::uint16_t port)
{
    WSADATA socketData;
    if (WSAStartup(MAKEWORD(2, 2), &socketData) != 0)
    {
        LOG_ERROR("Socket was not initialized. Cause: " + WSAGetLastError());
        throw Exceptions::NetworkException("Socket was not initialized");
    }

    if ((mSocketHandle = (int) socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        LOG_ERROR("Socket was not created. Cause: " + WSAGetLastError());
        throw Exceptions::NetworkException("Socket was not created");
    }

    memset((char*) &mSocketAddress, 0, sizeof(mSocketAddress));
    mSocketAddress.sin_family = AF_INET;
    mSocketAddress.sin_port = htons(port);
    mSocketAddress.sin_addr.S_un.S_addr = inet_addr(ipAddress);
}

void Platforms::Network::UDPConnection::sendBuffer(void* buffer) noexcept
{
    sendto(mSocketHandle, reinterpret_cast<char*>(buffer), MAX_PACKET_SIZE, 0, (struct sockaddr*) &mSocketAddress, MAX_PACKET_SIZE);
}

void Platforms::Network::UDPConnection::receiveBuffer(void* buffer) noexcept
{
    int sizeStub = 0;
    recvfrom(mSocketHandle, reinterpret_cast<char*>(buffer), MAX_PACKET_SIZE, 0, (struct sockaddr*) &mSocketAddress, &sizeStub);
}

Platforms::Network::UDPConnection::~UDPConnection()
{
    closesocket(mSocketHandle);
    WSACleanup();
}
