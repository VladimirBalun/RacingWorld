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

namespace Core::Managers 
{

    template<class T>
    struct IManager;

    class SoundManager;
    class LocaleManager;
    class ResourceManager;
    class ConfigurationManager;

}

#ifndef g_sound_manager
    #define g_sound_manager Core::Managers::SoundManager::getInstance()
#endif // g_sound_manager

#ifndef g_locale_manager
    #define g_locale_manager Core::Managers::LocaleManager::getInstance()
#endif // g_locale_manager

#ifndef g_resource_manager
    #define g_resource_manager Core::Managers::ResourceManager::getInstance()
#endif // g_resource_manager

#ifndef g_configuration_manager
    #define g_configuration_manager Core::Managers::ConfigurationManager::getInstance()
#endif // g_configuration_manager
