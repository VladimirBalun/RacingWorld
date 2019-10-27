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
#include "ResourceManager.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "ConfigurationManager.hpp"
#include "../Resources.hpp"
#include "../Helpers/Time.hpp"
#include "../Helpers/Debug.hpp"

void Core::Managers::ResourceManager::initialize()
{
#ifdef _DEBUG
    const auto start_time = Helpers::getCurrentTimeInMilliseconds<double>();
#endif // _DEBUG

    const std::string resources_path = g_configuration_manager.getResourcesPath();
    const std::string resources_config_filename = g_configuration_manager.getResourcesConfigurationFilename();
    const std::string resources_config_file_full_path = resources_path + resources_config_filename;

    try
    {
        boost::property_tree::ptree ini_configuration{};
        read_ini(resources_config_file_full_path, ini_configuration);
        loadSection<Resources::Model>(ini_configuration.get_child("Models"));
        loadSection<Resources::Sound>(ini_configuration.get_child("Sounds"));
        loadSection<Resources::Image>(ini_configuration.get_child("Textures"));
        loadSection<Resources::VertexShader>(ini_configuration.get_child("VertexShaders"));
        loadSection<Resources::FragmentShader>(ini_configuration.get_child("FragmentShaders"));
    }
    catch (const boost::property_tree::ini_parser_error&)
    {
        LOG_ERROR("'PlayerManager' was not initialized.");
    }

#ifdef _DEBUG
    const auto end_time = Helpers::getCurrentTimeInMilliseconds<double>();
    const auto loading_time = end_time - start_time;
    LOG_PROFILING("'ResourceManager' was initialized in " + TO_STR(loading_time) + "ms.");
#endif // _DEBUG
}
