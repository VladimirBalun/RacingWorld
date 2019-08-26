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
#include <unordered_map>
#include <libxl.h>

#include "IManager.hpp"

#ifndef g_locale_manager
    #define g_locale_manager Core::Managers::LocaleManager::getInstance()
#endif // g_locale_manager

namespace Core { namespace Managers {

    class LocaleManager : public IManager<LocaleManager>
    {
    public:
        static LocaleManager& getInstance() noexcept;
    public:
        void initialize();
        std::string getString(const std::string& key) const noexcept;
    private:
        void findNecessaryColIndexesInSheet(libxl::Sheet* sheet, int& key_index, int& data_index) const noexcept;
        void readAllStringFromSheet(libxl::Sheet* sheet, int key_index, int data_index) noexcept;
    private:
        LocaleManager() noexcept = default;
        explicit LocaleManager(const LocaleManager& other) noexcept = delete;
        LocaleManager& operator = (const LocaleManager& other) noexcept = delete;
    private:
        std::unordered_map<std::string, std::string> m_strings{};
    };

}}


