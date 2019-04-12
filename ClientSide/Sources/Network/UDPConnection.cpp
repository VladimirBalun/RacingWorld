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

Network::UDPConnection::UDPConnection(const String& address, std::uint16_t port) noexcept
{
    WSADATA socketData;
    if (WSAStartup(MAKEWORD(2, 2), &socketData) != 0)
        LOG_ERROR("Socket was not initialized. Cause: " + WSAGetLastError());

    if ((mSocketHandle = (int) socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
        LOG_ERROR("Socket was not created. Cause: " + WSAGetLastError());

    memset((char*) &mSocketAddress, 0, sizeof(mSocketAddress));
    mSocketAddress.sin_family = AF_INET;
    mSocketAddress.sin_port = htons(port);
    mSocketAddress.sin_addr.S_un.S_addr = inet_addr(address.getData());
}

void Network::UDPConnection::sendBuffer(char* buffer, std::size_t size) noexcept
{
    int statusCode = sendto(mSocketHandle, buffer, MAX_PACKET_SIZE, 0, (struct sockaddr*) &mSocketAddress, (int) size);
    if (statusCode <= 0)
        LOG_WARNING("Error during sending of the packet.");
}

void Network::UDPConnection::receiveBuffer(char* buffer) noexcept
{
    int statusCode = recvfrom(mSocketHandle, buffer, MAX_PACKET_SIZE, 0, 0, 0);
    if (statusCode <= 0)
        LOG_WARNING("Error during getting of the packet.");
}

Network::UDPConnection::~UDPConnection()
{
    closesocket(mSocketHandle);
    WSACleanup();
}
