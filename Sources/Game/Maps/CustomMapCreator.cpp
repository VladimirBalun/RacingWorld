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
#include "CustomMapCreator.hpp"

#include "Core/Resources/Text.hpp"
#include "Core/Managers/ResourceManager.hpp"
#include "Core/Managers/ConfigurationManager.hpp"

Game::Maps::Map Game::Maps::CustomMapCreator::createImpl(const std::string& map_filename)
{
    Core::Resources::Text map_data = readMapData(map_filename);
    return Map{};
}

Core::Resources::Text Game::Maps::CustomMapCreator::readMapData(const std::string& map_filename)
{
    std::string_view maps_directory = g_configuration_manager.getMapsPath();
    std::string map_full_path = STR(maps_directory) + map_filename;

    std::optional<Core::Resources::Text> map_data = g_resource_manager.loadResource<Core::Resources::Text>(map_full_path);
    if (!map_data.has_value())
    {
        throw std::runtime_error("Maps data were not loaded.");
    }

    return map_data.value();
}
