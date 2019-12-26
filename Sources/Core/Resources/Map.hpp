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

#include "Aliases.hpp"
#include "IResource.hpp"
#include "../Helpers/Holders/Polymorphic.hpp"

namespace Core::Resources
{

    class Map : public IResource, public Helpers::Holders::Polymorphic<Map>
    {
    public:
        class MapObject
        {
        public:
            void setScale(float scale) noexcept;
            void setXRotation(float rotation) noexcept;
            void setYRotation(float rotation) noexcept;
            void setZRotation(float rotation) noexcept;
            void setPosition(const bg::point3f_t& position) noexcept;
            float getScale() const noexcept;
            float getXRotation() const noexcept;
            float getYRotation() const noexcept;
            float getZRotation() const noexcept;
            const bg::point3f_t& getPosition() const noexcept;
        private:
            bg::point3f_t m_position{};
            float m_scale = 1.0f;
            float m_x_rotation = 1.0f;
            float m_y_rotation = 1.0f;
            float m_z_rotation = 1.0f;
        };
    public:
        void setDimensions(const bg::box2f_t& dimensions) noexcept;
        void setTreeModelsName(const std::string& model_name);
        void setHouseModelsName(const std::string& model_name);
        void setGroundModelsName(const std::string& model_name);
        void setTreeObjects(std::vector<MapObject>&& map_objects) noexcept;
        void setHouseObjects(std::vector<MapObject>&& map_objects) noexcept;
        void setGroundObjects(std::vector<MapObject>&& map_objects) noexcept;
        const bg::box2f_t& getDimensions() const noexcept;
        std::string_view getTreeModelsName() const noexcept;
        std::string_view getHouseModelsName() const noexcept;
        std::string_view getGroundModelsName() const noexcept;
        const std::vector<MapObject>& getTreeObjects() const noexcept;
        const std::vector<MapObject>& getHouseObjects() const noexcept;
        const std::vector<MapObject>& getGroundObjects() const noexcept;
    public:
        bool load(std::string_view map_path) noexcept override;
    private:
        std::string m_tree_models_name{};
        std::string m_house_models_name{};
        std::string m_ground_models_name{};
        std::vector<MapObject> m_tree_objects{};
        std::vector<MapObject> m_house_objects{};
        std::vector<MapObject> m_ground_objects{};
        bg::box2f_t m_map_dimensions{};
    };

}
