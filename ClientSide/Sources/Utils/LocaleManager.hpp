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

#define g_locale_manager LocaleManager::getInstance()

#define ENGLISH_LANGUAGE "English"
#define RUSSIAN_LANGUAGE "Russian"

#define IS_ENGLISH_LANGUAGE \
    g_locale_manager->getCurrentLanguage() == ENGLISH_LANGUAGE

#define IS_RUSSIAN_LANGUAGE \
    g_locale_manager->getCurrentLanguage() == RUSSIAN_LANGUAGE

// Singleton
class LocaleManager
{
public:
    static LocaleManager& getInstance() noexcept;
    void initialize() noexcept;
    std::string getCurrentLanguage() const noexcept;
    std::string getString(const std::string& key) const noexcept;
private:
    std::string m_current_language{};
    std::unordered_map<std::string, std::string> m_strings{};
};
