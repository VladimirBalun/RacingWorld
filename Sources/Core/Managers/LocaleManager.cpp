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

#include "PrecompiledHeader.hpp"
#include "LocaleManager.hpp"

#include "ConfigurationManager.hpp"
#include "../Helpers/Time.hpp"
#include "../Helpers/Debug.hpp"
#include "../Helpers/Macroses.hpp"

void Core::Managers::LocaleManager::initialize()
{
#ifdef _DEBUG
    const auto start_time = Helpers::getCurrentTimeInMilliseconds<double>();
#endif // _DEBUG

    if (libxl::Book* book = xlCreateBook())
    {
        const std::string resources_path = g_configuration_manager.getResourcesPath();
        const std::string locales_config_filename = g_configuration_manager.getLocalesConfigurationFilename();
        const std::string locales_config_file_full_path = resources_path + locales_config_filename;
        if (book->load(locales_config_file_full_path.c_str()))
        {
            if (libxl::Sheet* sheet = book->getSheet(0))
            {
                int key_index_cow = 0;
                int data_index_cow = 0;
                findNecessaryColIndexesInSheet(sheet, key_index_cow, data_index_cow);
                readAllStringFromSheet(sheet, key_index_cow, data_index_cow);
            }
        }
        else
        {
            LOG_ERROR("'LocaleManager' was not initialized. Cause: file '" + locales_config_file_full_path + "' was not loaded.");
        }
        book->release();
    }
    else
    {
        LOG_ERROR("'LocaleManager' was not initialized. Cause: LibXL internal error.");
    }

#ifdef _DEBUG
    const auto end_time = Helpers::getCurrentTimeInMilliseconds<double>();
    const auto loading_time = end_time - start_time;
    LOG_PROFILING("'LocaleManager' was initialized in " + TO_STR(loading_time) + "ms.");
#endif // _DEBUG
}

void Core::Managers::LocaleManager::findNecessaryColIndexesInSheet(libxl::Sheet* sheet, int& key_index, int& data_index) const noexcept
{
    const int header_row = 0;
    const std::string key_header_name = "Key";
    const std::string data_header_name = g_configuration_manager.getCurrentLanguage();
    for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
    {
        const std::string data = sheet->readStr(header_row, col);
        if (data == key_header_name)
        {
            key_index = col;
        }
        if (data == data_header_name)
        {
            data_index = col;
        }
    }
}

void Core::Managers::LocaleManager::readAllStringFromSheet(libxl::Sheet* sheet, const int key_index, const int data_index) noexcept
{
    for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
    {
        const std::string key = sheet->readStr(row, key_index);
        const std::string data = sheet->readStr(row, data_index);
        m_strings.emplace(key, data);
    }
}

std::string Core::Managers::LocaleManager::getString(const std::string& key) const noexcept
{
    const auto& it = m_strings.find(key);
    return (it != end(m_strings)) ? (it->second) : ("");
}
