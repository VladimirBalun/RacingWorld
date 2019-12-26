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


#include "Aliases.hpp"
#include "../Map.hpp"

namespace Core::Resources
{

    class Text;

    namespace Loaders
    {

        class MapLoader
        {
        public:
            static bool load(Map& map, std::string_view map_file_path) noexcept;
        private:
            static void loadDimensions(Map& map, const bpt::ptree::value_type& xml_value);
            static void loadObjectModelsIdentifiers(Map& map, const bpt::ptree& xml_models);
            static Map::MapObject getMapObjectFromXML(const bpt::ptree::value_type& xml_value);
            static std::vector<Map::MapObject> getSetMapObjectsFromXML(const bpt::ptree& xml_object);
        };

    }

}
