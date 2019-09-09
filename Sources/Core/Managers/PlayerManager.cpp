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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "ConfigurationManager.hpp"
#include "../Helpers/Time.hpp"
#include "../Helpers/Debug.hpp"
#include "../Helpers/Macroses.hpp"

void Core::Managers::PlayerManager::initialize()
{
#ifdef _DEBUG
    const auto start_time = Helpers::getCurrentTimeInMilliseconds<double>();
#endif // _DEBUG

    using namespace boost::property_tree;
    const std::string resources_path = g_configuration_manager.getResourcesPath();
    const std::string player_config_filename = g_configuration_manager.getPlayerConfigurationFilename();
    const std::string player_config_file_full_path = resources_path + player_config_filename;

    try
    {
        ptree xml_configuration{};
        read_xml(player_config_file_full_path, xml_configuration);
        for (const auto& xml_data : xml_configuration.get_child("player"))
        {
            m_email = xml_data.second.get<std::string>("<xmlattr>.email", "");
            m_password = xml_data.second.get<std::string>("<xmlattr>.password", "");
        }
    }
    catch (const xml_parser_error&)
    {
        LOG_ERROR("'PlayerManager' was not initialized.");
        //NOTIFY_EVENT(GLOBAL_ERROR_EVENT_TYPE, "Player configuration was not loaded.");
    }

#ifdef _DEBUG
    const auto end_time = Helpers::getCurrentTimeInMilliseconds<double>();
    const auto loading_time = end_time - start_time;
    LOG_PROFILING("'PlayerManager' was initialized in " + TO_STR(loading_time) + "ms.");
#endif // _DEBUG
}

std::string Core::Managers::PlayerManager::getEmail() const noexcept
{
    return m_email;
}

std::string Core::Managers::PlayerManager::getPassword() const noexcept
{
    return m_password;
}
