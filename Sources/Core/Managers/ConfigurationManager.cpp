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

#include "ConfigurationManager.hpp"

#include <filesystem>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "../Helpers/Time.hpp"
#include "../Helpers/Debug.hpp"
#include "../Helpers/Macroses.hpp"

void Core::Managers::ConfigurationManager::initialize()
{
#ifdef _DEBUG
    const auto start_time = Helpers::getCurrentTimeInMilliseconds<double>();
#endif // _DEBUG

    using namespace boost::property_tree;
    const std::string configuration_filename = "Configuration.xml";
    const std::string configuration_file_full_path = getResourcesPath() + configuration_filename;

    try
    {
        ptree xml_configuration{};
        read_xml(configuration_file_full_path, xml_configuration);
        for (const auto& xml_data : xml_configuration.get_child("configuration"))
        {
            if (xml_data.first == "server")
            {
                m_server_port = xml_data.second.get<std::uint16_t>("<xmlattr>.port", 0u);
                m_server_address = xml_data.second.get<std::string>("<xmlattr>.address", "");
            }
            if (xml_data.first == "language")
            {
                m_current_language = xml_data.second.get<std::string>("<xmlattr>.data", "");;
            }
            if (xml_data.first == "locales-config-filename")
            {
                m_locales_file_configuration_path = xml_data.second.get<std::string>("<xmlattr>.filename", "");;
            }
            if (xml_data.first == "player-config-filename")
            {
                m_player_file_configuration_path = xml_data.second.get<std::string>("<xmlattr>.filename", "");;
            }
            if (xml_data.first == "resources-config-filename")
            {
                m_resources_file_configuration_path = xml_data.second.get<std::string>("<xmlattr>.filename", "");;
            }
        }
    }
    catch (const xml_parser_error&)
    {
        LOG_ERROR("'ConfigurationManager' was not initialized.");
        //NOTIFY_EVENT(GLOBAL_ERROR_EVENT_TYPE, "Global configuration was not loaded.");
    }

#ifdef _DEBUG
    const auto end_time = Helpers::getCurrentTimeInMilliseconds<double>();
    const auto loading_time = end_time - start_time;
    LOG_PROFILING("'ConfigurationManager' was initialized in " + TO_STR(loading_time) + "ms.");
#endif // _DEBUG
}

std::string Core::Managers::ConfigurationManager::getCurrentLanguage() const noexcept
{
    return m_current_language;
}

std::uint16_t Core::Managers::ConfigurationManager::getServerPort() const noexcept
{
    return m_server_port;
}

std::string Core::Managers::ConfigurationManager::getServerAddress() const noexcept
{
    return m_server_address;
}

std::string Core::Managers::ConfigurationManager::getModelsPath() const noexcept
{
    static const std::string models_path = getResourcesPath() + "/Models/";
    return models_path;
}

std::string Core::Managers::ConfigurationManager::getShadersPath() const noexcept
{
    static const std::string shaders_path = getResourcesPath() + "/Shaders/";
    return shaders_path;
}

std::string Core::Managers::ConfigurationManager::getResourcesPath() const noexcept
{
    static const std::string resources_path = (std::filesystem::current_path().parent_path() / "Resources" / "").string();
    return resources_path;
}

std::string Core::Managers::ConfigurationManager::getLocalesConfigurationFilename() const noexcept
{
    return m_locales_file_configuration_path;
}

std::string Core::Managers::ConfigurationManager::getPlayerConfigurationFilename() const noexcept
{
    return m_player_file_configuration_path;
}

std::string Core::Managers::ConfigurationManager::getResourcesConfigurationFilename() const noexcept
{
    return m_resources_file_configuration_path;
}
