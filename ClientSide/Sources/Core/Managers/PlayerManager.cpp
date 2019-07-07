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

#include "PlayerManager.hpp"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "ConfigurationManager.hpp"
#include "../../EventSystem.hpp"

Core::Managers::PlayerManager& Core::Managers::PlayerManager::getInstance() noexcept
{
    static PlayerManager instance{};
    return instance;
}

void Core::Managers::PlayerManager::initialize()
{
    const std::string resources_path = g_configuration_manager.getResourcesPath();
    const std::string player_config_filename = g_configuration_manager.getPlayerConfigurationFilename();
    const std::string player_config_file_full_path = resources_path + player_config_filename;

    try
    {
        boost::property_tree::ptree xml_configuration{};
        boost::property_tree::read_xml(player_config_file_full_path, xml_configuration);
        BOOST_FOREACH(const auto& xml_data, xml_configuration.get_child("player"))
        {
            m_email = xml_data.second.get<std::string>("<xmlattr>.email", "");
            m_password = xml_data.second.get<std::string>("<xmlattr>.password", "");
        }
    }
    catch (const boost::property_tree::xml_parser_error&)
    {
        NOTIFY_EVENT(GLOBAL_ERROR_EVENT_TYPE, "Player configuration was not loaded.");
    }

    //if (!isInitialized())
    //{
    //    NOTIFY_EVENT(GLOBAL_ERROR_EVENT_TYPE, "Player configuration was not loaded.");
    //}
}

bool Core::Managers::PlayerManager::isInitialized() const noexcept
{
    return !m_email.empty() && !m_password.empty();
}

std::string Core::Managers::PlayerManager::getEmail() const noexcept
{
    return m_email;
}

std::string Core::Managers::PlayerManager::getPassword() const noexcept
{
    return m_password;
}
