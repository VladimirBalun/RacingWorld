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

#include <string>

#include "IManager.hpp"

#ifndef g_player_manager
    #define g_player_manager Core::Managers::PlayerManager::getInstance()
#endif // g_player_manager

namespace Core { namespace Managers {

    class PlayerManager : public IManager<PlayerManager>
    {
    public:
        static PlayerManager& getInstance() noexcept;
    public:
        void initialize();
        std::string getEmail() const noexcept;
        std::string getPassword() const noexcept;
    private:
        PlayerManager() noexcept = default;
        explicit PlayerManager(const PlayerManager& other) noexcept = delete;
        PlayerManager& operator = (const PlayerManager& other) noexcept = delete;
    private:
        std::string m_email{};
        std::string m_password{};
    };

}}
