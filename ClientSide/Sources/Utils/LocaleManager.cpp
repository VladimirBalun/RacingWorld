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

#include "LocaleManager.hpp"

LocaleManager& LocaleManager::getInstance() noexcept
{
    static LocaleManager instance;
    return instance;
}

void LocaleManager::initialize() noexcept
{
    
}

std::string LocaleManager::getCurrentLanguage() const noexcept
{
    return m_current_language;
}

std::string LocaleManager::getString(const std::string& key) const noexcept
{
    const auto& it = m_strings.find(key);
    return (it != end(m_strings)) ? (it->second) : ("");
}
