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

#define NETWORK_EVENT_TYPE EventSystem::Event::Type::NETWORK
#define GLOBAL_ERROR_EVENT_TYPE EventSystem::Event::Type::GLOBAL_ERROR

namespace EventSystem {

    class Event
    {
    public:
        enum class Type
        {
            NETWORK,
            GLOBAL_ERROR,

            COUNT_EVENT_TYPES,
            UNKNOWN
        };
    public:
        Event(Type type) noexcept
            : m_type(type) {}
    private:
        Type m_type = Type::UNKNOWN;
    };

}
