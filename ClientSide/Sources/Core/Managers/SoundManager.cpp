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

#include "SoundManager.hpp"

#include "ResourceManager.hpp"
#include "../Resources.hpp"
#include "../Helpers/Time.hpp"
#include "../Helpers/Debug.hpp"
#include "../Helpers/Macroses.hpp"

Core::Managers::SoundManager& Core::Managers::SoundManager::getInstance() noexcept
{
    static SoundManager instance{};
    return instance;
}

void Core::Managers::SoundManager::initialize()
{
#ifdef _DEBUG
    const auto start_time = Helpers::getCurrentTimeInMilliseconds<double>();
#endif // _DEBUG

#ifdef _DEBUG
    const auto end_time = Helpers::getCurrentTimeInMilliseconds<double>();
    const auto loading_time = end_time - start_time;
    LOG_PROFILING("'SoundManager' was initialized in " + TO_STR(loading_time) + "ms.");
#endif // _DEBUG
}

void Core::Managers::SoundManager::playSound(const std::string& key) noexcept
{
    if (!m_sounds.contains(key))
    {
        if (const auto sound = g_resource_manager.getResource<Resources::Sound>(key))
        {
            const auto output_sound_stream = sound->getAudioStream();
            m_sounds.insert(key, output_sound_stream);
        }
        else
        {
            LOG_WARNING("Sound '" + key + "' was not played. It's absent in the 'ResourceManager'.");
            return;
        }
    }

    const auto it = m_sounds.get(key);
    if (it.has_value())
    {
        if (const auto audio_stream = it.value())
        {
            audio_stream->play();
        }
    }
}

void Core::Managers::SoundManager::playMusic(const std::string& key) noexcept
{

}

const audiere::AudioDevicePtr& Core::Managers::SoundManager::getAudioDevice() const noexcept
{
    return m_device;
}
