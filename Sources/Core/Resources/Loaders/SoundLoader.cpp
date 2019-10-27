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

#include "PrecompiledHeader.hpp"
#include "SoundLoader.hpp"

#include <audiere.h>

#include "../Sound.hpp"
#include "../../Managers/SoundManager.hpp"

bool Core::Resources::Loaders::SoundLoader::load(Sound& sound, const std::string& sound_file_path, const bool streaming) noexcept
{
    const audiere::AudioDevicePtr& audio_device = g_sound_manager.getAudioDevice();
    audiere::OutputStreamPtr audio_stream = OpenSound(audio_device, sound_file_path.c_str(), streaming);
    if (audio_stream)
    {
        sound.setAudioStream(std::move(audio_stream));
        return true;
    }

    return  false;
}
