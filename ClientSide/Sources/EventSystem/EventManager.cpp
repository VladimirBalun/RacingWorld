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

#include "EventManager.hpp"

EventSystem::EventManager& EventSystem::EventManager::getInstance() noexcept
{
    static EventManager event_manager;
    return event_manager;
}

void EventSystem::EventManager::notifyGlobalError(const char* message) noexcept
{
    for (std::uint8_t i = 0; i < MAX_COUNT_GLOBAL_ERROR_SUBSCRIBERS; i++)
        if (m_global_error_subscribers[i])
            m_global_error_subscribers[i]->onEvent(message);
}

void EventSystem::EventManager::subscribeOnGlobalError(const IEventSubscriber& subscriber) noexcept
{
    for (std::uint8_t i = 0; i < MAX_COUNT_GLOBAL_ERROR_SUBSCRIBERS; i++)
    {
        if (!m_global_error_subscribers[i])
        {
            m_global_error_subscribers[i] = &subscriber;
            return;
        }
    }

    ASSERT(false, "Subcribers on global errors not enought.");
}
