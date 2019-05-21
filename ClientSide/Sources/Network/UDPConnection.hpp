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
#include <boost/asio.hpp>

namespace Network {

    class UDPConnection
    {
        static const std::uint16_t MAX_PACKET_SIZE = 1024u;
    public:
        explicit UDPConnection(const std::string_view& address, std::uint16_t port) noexcept;
        bool connect() noexcept;
        void read(char* to_data, std::size_t size);
        void write(const char* from_data, std::size_t size);
        ~UDPConnection();
    private:
        boost::asio::io_service m_io_service{};
        boost::asio::ip::udp::endpoint m_server_endpoint;
        boost::asio::ip::udp::socket m_socket;
    };

}
