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

Network::UDPConnection::UDPConnection(const std::string_view& address, std::uint16_t port) noexcept
{
    WSADATA socket_data;
    if (WSAStartup(MAKEWORD(2, 2), &socket_data) != 0)
        LOG_ERROR("Socket was not initialized. Cause: " + WSAGetLastError());

    if ((m_socket_handle = (int) socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
        LOG_ERROR("Socket was not created. Cause: " + WSAGetLastError());

    memset((char*) &m_socket_address, 0, sizeof(m_socket_address));
    m_socket_address.sin_family = AF_INET;
    m_socket_address.sin_port = htons(port);
    m_socket_address.sin_addr.S_un.S_addr = inet_addr(address.data());
}

void Network::UDPConnection::sendBuffer(char* buffer, std::size_t size) noexcept
{
    const int status_code = sendto(m_socket_handle, buffer, MAX_PACKET_SIZE, 0, (struct sockaddr*) &m_socket_address, (int) size);
    if (status_code <= 0)
        LOG_WARNING("Error during sending of the packet.");
}

void Network::UDPConnection::receiveBuffer(char* buffer) noexcept
{
    const int status_code = recvfrom(m_socket_handle, buffer, MAX_PACKET_SIZE, 0, 0, 0);
    if (status_code <= 0)
        LOG_WARNING("Error during getting of the packet.");
}

Network::UDPConnection::~UDPConnection()
{
    closesocket(m_socket_handle);
    WSACleanup();
}
