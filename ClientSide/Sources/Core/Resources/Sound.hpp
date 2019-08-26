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

#include "IResource.hpp"
#include "../ManagersFWD.hpp"

namespace Core { namespace Resources { namespace Loaders {

    class WAVLoader;
    class MP3Loader;
    class OGGLoader;

}}}

namespace Core { namespace Resources {

    class Sound : public IResource
    {
        friend class Loaders::WAVLoader;
        friend class Loaders::MP3Loader;
        friend class Loaders::OGGLoader;
        friend class Managers::ResourceManager;
    public:
        audiere::OutputStreamPtr getAudioStream() const noexcept;
    private:
        bool load(const std::string& sound_path) noexcept override;
        void setAudioStream(audiere::OutputStreamPtr&& audio_stream) noexcept;
    private:
        audiere::OutputStreamPtr m_audio_stream = nullptr;
    };

}}
