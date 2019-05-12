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

#include <array>
#include <utility>
#include <cstdint>

#include "IEventSubscriber.hpp"
#include "../Utils/Debug.hpp"

#define MAX_COUNT_GLOBAL_ERROR_SUBSCRIBERS 5

namespace EventSystem {

    // Singleton
    class EventManager
    {
    public:
        static EventManager& getInstance() noexcept;
        void notifyGlobalError(const char* message) noexcept;
        void subscribeOnGlobalError(const IEventSubscriber& subscriber) noexcept;
    private:
        std::array<const IEventSubscriber*, MAX_COUNT_GLOBAL_ERROR_SUBSCRIBERS> m_global_error_subscribers{};
    };

}
