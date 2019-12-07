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

#include <audiere.h>

#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core::Resources 
{

    class Sound final : public IResource, public Helpers::Holders::Polymorphic<Sound>
    {
    public:
        audiere::OutputStreamPtr getAudioStream() const noexcept;
        void setAudioStream(audiere::OutputStreamPtr&& audio_stream) noexcept;
    public:
        bool load(std::string_view sound_path) noexcept override;
    private:
        audiere::OutputStreamPtr m_audio_stream = nullptr;
    };

}
