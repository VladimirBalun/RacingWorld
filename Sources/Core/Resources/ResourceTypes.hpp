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

#include "../ResourcesFWD.hpp"

namespace Core { namespace Resources {

    enum class ResourceType
    {
        UNKNOWN = 0,
        MATERIAL_TYPE,
        SOUND_TYPE,
        MODEL_TYPE,
        TEXTURE_TYPE,
        TEXT_TYPE,

        // Must be last
        COUNT_TYPES
    };

    template<typename T>
    constexpr ResourceType getResourceType() noexcept
    {
        if (std::is_same<T, Material>::value)
            return ResourceType::MATERIAL_TYPE;
        if (std::is_same<T, Model>::value)
            return ResourceType::MODEL_TYPE;
        if (std::is_same<T, Sound>::value)
            return ResourceType::SOUND_TYPE;
        if (std::is_same<T, Texture>::value)
            return ResourceType::TEXTURE_TYPE;
        if (std::is_same<T, Text>::value)
            return ResourceType::TEXT_TYPE;

        return ResourceType::UNKNOWN;
    }

}}
