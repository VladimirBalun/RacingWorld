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

#include "Sound.hpp"

#include <functional>
#include <unordered_map>
#include <boost/filesystem/convenience.hpp>

#include "Loaders/SoundLoader.hpp"

audiere::OutputStreamPtr Core::Resources::Sound::getAudioStream() const noexcept
{
    return m_audio_stream;
}

bool Core::Resources::Sound::load(const std::string& sound_path) noexcept
{
    using SoundLoader = std::function<bool(Core::Resources::Sound&, const std::string&, bool)>;
    static const std::unordered_map<std::string, SoundLoader> available_loaders = {
        { ".wav", std::bind(&Loaders::WAVLoader::load, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3) },
        { ".mp3", std::bind(&Loaders::MP3Loader::load, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3) },
        { ".ogg", std::bind(&Loaders::OGGLoader::load, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3) }
    };

    const std::string extension = boost::filesystem::extension(sound_path);
    const auto& it = available_loaders.find(extension);
    if (it != end(available_loaders))
    {
        if (const SoundLoader& sound_loader = it->second)
        {
            return sound_loader(*this, sound_path, false);
        }
    }

    return false;
}

void Core::Resources::Sound::setAudioStream(audiere::OutputStreamPtr&& audio_stream) noexcept
{
    m_audio_stream = audio_stream;
}
