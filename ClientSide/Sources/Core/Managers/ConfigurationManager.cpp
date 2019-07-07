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
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "../../EventSystem.hpp"

Core::Managers::ConfigurationManager& Core::Managers::ConfigurationManager::getInstance() noexcept
{
    static ConfigurationManager instance;
    return instance;
}

void Core::Managers::ConfigurationManager::initialize()
{
    const std::string configuration_filename = "Configuration.xml";
    const std::string configuration_file_full_path = getResourcesPath() + configuration_filename;

    try
    {
        boost::property_tree::ptree xml_configuration{};
        boost::property_tree::read_xml(configuration_file_full_path, xml_configuration);
        BOOST_FOREACH(const auto& xml_data, xml_configuration.get_child("configuration"))
        {
            if (xml_data.first == "server")
            {
                m_server_port = xml_data.second.get<std::uint16_t>("<xmlattr>.port", 0u);
                m_server_address = xml_data.second.get<std::string>("<xmlattr>.address", "");
            }
            if (xml_data.first == "locales")
            {
                m_locales_file_configuration_path = xml_data.second.get<std::string>("<xmlattr>.filename", "");;
            }
            if (xml_data.first == "player")
            {
                m_player_file_configuration_path = xml_data.second.get<std::string>("<xmlattr>.filename", "");;
            }
            if (xml_data.first == "resources")
            {
                m_resources_file_configuration_path = xml_data.second.get<std::string>("<xmlattr>.filename", "");;
            }
            if (xml_data.first == "language")
            {
                m_current_language = xml_data.second.get<std::string>("<xmlattr>.data", "");;
            }
        }
    }
    catch (const boost::property_tree::xml_parser_error&)
    {
        NOTIFY_EVENT(GLOBAL_ERROR_EVENT_TYPE, "Global configuration was not loaded.");
    }

    if (!isInitialized())
    {
        NOTIFY_EVENT(GLOBAL_ERROR_EVENT_TYPE, "Global configuration was not loaded.");
    }
}

bool Core::Managers::ConfigurationManager::isInitialized() const noexcept
{
    return m_server_port != 0u
        && !m_server_address.empty()
        && !m_locales_file_configuration_path.empty()
        && !m_player_file_configuration_path.empty()
        && !m_resources_file_configuration_path.empty();
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
