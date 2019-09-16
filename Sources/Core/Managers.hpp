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

#include <thread>
#include <boost/asio.hpp>

#include "Managers/SoundManager.hpp"
#include "Managers/LocaleManager.hpp"
#include "Managers/PlayerManager.hpp"
#include "Managers/ResourceManager.hpp"
#include "Managers/ConfigurationManager.hpp"

#define g_sound_manager         Core::Managers::SoundManager::getInstance()
#define g_locale_manager        Core::Managers::LocaleManager::getInstance()
#define g_player_manager        Core::Managers::PlayerManager::getInstance()
#define g_resource_manager      Core::Managers::ResourceManager::getInstance()
#define g_configuration_manager Core::Managers::ConfigurationManager::getInstance()

namespace Core { namespace Managers {

    inline void initialize() noexcept
    {
        g_configuration_manager.initialize();
        g_sound_manager.initialize();

        boost::asio::thread_pool thread_pool(std::thread::hardware_concurrency());
        post(thread_pool, [] { g_resource_manager.initialize(); });
        post(thread_pool, [] { g_locale_manager.initialize(); });
        post(thread_pool, [] { g_player_manager.initialize(); });
        thread_pool.join();
    }

}}
