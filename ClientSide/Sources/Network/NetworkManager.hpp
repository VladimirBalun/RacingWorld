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

#include "UDPConnection.hpp"
#include "../Utils/Configuration.hpp"

namespace Network {

    // Singleton
    class NetworkManager
    {
    public:
        static NetworkManager& getInstance() noexcept;
        bool connect() noexcept;
        bool login() noexcept;
        bool logout() noexcept;
        bool isConnected() const noexcept;
        bool isLogin() const noexcept;
    private:
        NetworkManager() noexcept
            : m_connection(Configuration::Network::SERVER_ADDRESS, Configuration::Network::SERVER_PORT) {}
        explicit NetworkManager(const NetworkManager& other) noexcept = delete;
        NetworkManager& operator = (const NetworkManager& other) noexcept = delete;
    private:
        UDPConnection m_connection;
        bool m_is_connected = false;
        bool m_is_login = false;
        std::int32_t m_current_token = 0;
        std::int32_t m_packet_number = 1;
    };

}