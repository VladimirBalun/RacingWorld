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

#include "EventSystem/Event.hpp"
#include "EventSystem/EventManager.hpp"
#include "EventSystem/IEventSubscriber.hpp"

#ifndef g_event_manager
    #define g_event_manager EventSystem::EventManager::getInstance()
#endif // g_event_manager

#define NOTIFY_EVENT(__event_type__, __data__) \
    g_event_manager.notifyEvent((__event_type__), (__data__))

#define SUBSCRIBE_ON_EVENT(__event_type__, __instance__) \
    g_event_manager.subscribeOnEventType((__event_type__), (__instance__))

#define UNSUBSCRIBE_FROM_EVENT(__event_type__, __instance__) \
    g_event_manager.unsubscribeFromEventType((__event_type__), (__instance__))
