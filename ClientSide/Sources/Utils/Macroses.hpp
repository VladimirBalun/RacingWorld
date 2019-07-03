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

#include <memory>


#define g_event_manager   EventSystem::EventManager::getInstance()
#define g_mesh_manager    Graphics::Managers::MeshManager::getInstance()
#define g_shader_manager  Graphics::Managers::ShaderManager::getInstance()
#define g_locale_manager  LocaleManager::getInstance()
#define g_network_manager Network::NetworkManager::getInstance()


#define NOTIFY_EVENT(__event_type__, __data__) \
    g_event_manager.notifyEvent((__event_type__), (__data__))

#define SUBSCRIBE_ON_EVENT(__event_type__, __instance__) \
    g_event_manager.subscribeOnEventType((__event_type__), (__instance__))


#define STRINGIFY(__value__) #__value__


#define DECLARE_SMART_PTR_FOR_CLASS(__class_name__) \
    using __class_name__##SPTR = std::shared_ptr<__class_name__>; \
    using __class_name__##UPTR = std::unique_ptr<__class_name__>; \
    using __class_name__##WPTR = std::weak_ptr<__class_name__>;

#define DECLARE_SMART_PTR_FOR_STRUCT(__struct_name__) \
    using __struct_name__##SPTR = std::shared_ptr<__struct_name__>; \
    using __struct_name__##UPTR = std::unique_ptr<__struct_name__>; \
    using __struct_name__##WPTR = std::weak_ptr<__struct_name__>;

#define FORWARD_DECLARE_SMART_PTR_FOR_CLASS(__class_name__) \ 
    class __class_name__; \
    DECLARE_SMART_PTR_FOR_CLASS(__class_name__)

#define FORWARD_DECLARE_SMART_PTR_FOR_STRUCT(__struct_name__) \ 
    class __struct_name__; \
    DECLARE_SMART_PTR_FOR_STRUCT(__struct_name__)
