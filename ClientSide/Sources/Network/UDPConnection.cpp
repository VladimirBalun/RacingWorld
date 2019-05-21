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
    : m_server_endpoint(boost::asio::ip::address::from_string(address.data()), port), 
      m_socket(m_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
{
#ifdef _DEBUG
    m_socket.set_option(boost::asio::ip::udp::socket::debug(true));
#endif
}

bool Network::UDPConnection::connect() noexcept
{
    m_socket.connect(m_server_endpoint);
    return m_socket.is_open();
}

void Network::UDPConnection::read(char* to_data, const std::size_t size)
{
    char buffer[MAX_PACKET_SIZE] = { 0 };
    boost::asio::ip::udp::endpoint sender_endpoint{};
    m_socket.receive(boost::asio::buffer(buffer, size));
    std::copy(buffer, buffer + size, to_data);
}

void Network::UDPConnection::write(const char* from_data, const std::size_t size)
{
    m_socket.send(boost::asio::buffer(from_data, size));
}

Network::UDPConnection::~UDPConnection()
{
    if (m_socket.is_open())
    {
        m_socket.cancel();
        m_socket.close();
    }
}
