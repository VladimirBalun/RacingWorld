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
    static EventManager eventManager;
    return eventManager;
}

const char* EventSystem::EventManager::getGlobalErrorMessage() const noexcept
{
    return mGlobalErrorMessage;
}

void EventSystem::EventManager::notifyGlobalError(const char* message) noexcept
{
    mGlobalErrorMessage = message;
    for (std::uint8_t i = 0; i < MAX_COUNT_GLOBAL_ERROR_SUBSCRIBERS; i++)
        if (mGlobalErrorSubscribers[i])
            mGlobalErrorSubscribers[i]->onEvent(message);
}

void EventSystem::EventManager::subscribeOnGlobalError(const IEventSubscriber& subscriber) noexcept
{
    for (std::uint8_t i = 0; i < MAX_COUNT_GLOBAL_ERROR_SUBSCRIBERS; i++)
    {
        if (!mGlobalErrorSubscribers[i])
        {
            mGlobalErrorSubscribers[i] = &subscriber;
            return;
        }
    }

    ASSERT(false, "Subcribers on global errors not enought.");
}
