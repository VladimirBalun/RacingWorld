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
#include "MapLoader.hpp"

#include "TextLoader.hpp"
#include "../Text.hpp"
#include "../../Helpers/Debug.hpp"

constexpr std::size_t X_COORDINATE = 0u;
constexpr std::size_t Y_COORDINATE = 1u;
constexpr std::size_t Z_COORDINATE = 2u;

bool Core::Resources::Loaders::MapLoader::load(Map& map, std::string_view map_file_path) noexcept
{
    try
    {
        bpt::ptree map_data{};
        read_xml(STR(map_file_path), map_data);
        for (const bpt::ptree::value_type& xml_value : map_data.get_child("map"))
        {
            if (xml_value.first == "dimensions")
            {
                loadDimensions(map, xml_value);
            }
            if (xml_value.first == "models")
            {
                loadObjectModelsIdentifiers(map, xml_value.second);
            }
            if (xml_value.first == "objects")
            {
                for (const bpt::ptree::value_type& xml_objects : xml_value.second)
                {
                    if (xml_objects.first == "trees")
                    {
                        std::vector<Map::MapObject> tree_objects = getSetMapObjectsFromXML(xml_objects.second);
                        map.setTreeObjects(std::move(tree_objects));
                    }
                    if (xml_objects.first == "houses")
                    {
                        std::vector<Map::MapObject> house_objects = getSetMapObjectsFromXML(xml_objects.second);
                        map.setHouseObjects(std::move(house_objects));
                    }
                }
            }
        }
    }
    catch (const bpt::xml_parser_error&)
    {
        LOG_ERROR("Map file: '" + STR(map_file_path) + "' was not read.");
        return false;
    }

    return true;
}

void Core::Resources::Loaders::MapLoader::loadDimensions(Map& map, const bpt::ptree::value_type& xml_value)
{
    bg::box2f_t dimensions{};
    dimensions.min_corner().set<X_COORDINATE>(xml_value.second.get<float>("<xmlattr>.xmin", 0.0f));
    dimensions.min_corner().set<Y_COORDINATE>(xml_value.second.get<float>("<xmlattr>.ymin", 0.0f));
    dimensions.max_corner().set<X_COORDINATE>(xml_value.second.get<float>("<xmlattr>.xmax", 0.0f));
    dimensions.max_corner().set<Y_COORDINATE>(xml_value.second.get<float>("<xmlattr>.ymax", 0.0f));
    map.setDimensions(dimensions);
}

void Core::Resources::Loaders::MapLoader::loadObjectModelsIdentifiers(Map& map, const bpt::ptree& xml_models)
{
    for (const bpt::ptree::value_type& xml_model : xml_models)
    {
        const std::string& objects_id = xml_model.second.get<std::string>("<xmlattr>.objects", "");
        if (objects_id == "trees")
        {
            map.setTreeModelsName(xml_model.second.get<std::string>("<xmlattr>.model", ""));
        }
        if (objects_id == "houses")
        {
            map.setHouseModelsName(xml_model.second.get<std::string>("<xmlattr>.model", ""));
        }
    }
}

std::vector<Core::Resources::Map::MapObject> Core::Resources::Loaders::MapLoader::getSetMapObjectsFromXML(const bpt::ptree& xml_objects)
{
    std::vector<Map::MapObject> map_objects{};
    map_objects.reserve(xml_objects.size());
    for (const bpt::ptree::value_type& xml_object : xml_objects)
    {
        Map::MapObject map_object = getMapObjectFromXML(xml_object);
        map_objects.push_back(std::move(map_object));
    }

    return map_objects;
}

Core::Resources::Map::MapObject Core::Resources::Loaders::MapLoader::getMapObjectFromXML(const bpt::ptree::value_type& xml_object)
{
    Map::MapObject map_object{};

    map_object.setScale(xml_object.second.get<float>("<xmlattr>.scale", 1.0f));
    map_object.setXRotation(xml_object.second.get<float>("<xmlattr>.xrotation", 0.0f));
    map_object.setYRotation(xml_object.second.get<float>("<xmlattr>.yrotation", 0.0f));
    map_object.setZRotation(xml_object.second.get<float>("<xmlattr>.zrotation", 0.0f));

    bg::point3f_t position{};
    position.set<X_COORDINATE>(xml_object.second.get<float>("<xmlattr>.x", 0.0f));
    position.set<Y_COORDINATE>(xml_object.second.get<float>("<xmlattr>.y", 0.0f));
    position.set<Z_COORDINATE>(xml_object.second.get<float>("<xmlattr>.z", 0.0f));
    map_object.setPosition(position);

    return map_object;
}
