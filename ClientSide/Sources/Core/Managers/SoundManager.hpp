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
#include <audiere.h>
#include <boost/compute/detail/lru_cache.hpp>

#include "IManager.hpp"
#include "../Helpers/Holders/Singleton.hpp"

#ifndef g_sound_manager
    #define g_sound_manager Core::Managers::SoundManager::getInstance()
#endif // g_sound_manager

namespace Core { namespace Managers {

    class SoundManager : public IManager<SoundManager>, public Helpers::Holders::Singleton<SoundManager>
    {
    public:
        void initialize();
        void playSound(const std::string& key) noexcept;
        void playMusic(const std::string& key) noexcept;
        const audiere::AudioDevicePtr& getAudioDevice() const noexcept;
    private:
        audiere::AudioDevicePtr m_device;
        boost::compute::detail::lru_cache<std::string, audiere::OutputStreamPtr> m_music = 5;
        boost::compute::detail::lru_cache<std::string, audiere::OutputStreamPtr> m_sounds = 15;
    };

}}
