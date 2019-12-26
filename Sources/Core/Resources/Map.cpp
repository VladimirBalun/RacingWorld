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
#include "Map.hpp"

#include "Loaders/MapLoader.hpp"

#pragma region MapObject

void Core::Resources::Map::MapObject::setScale(float scale) noexcept
{
    m_scale = scale;
}

void Core::Resources::Map::MapObject::setXRotation(float rotation) noexcept
{
    m_x_rotation = rotation;
}

void Core::Resources::Map::MapObject::setYRotation(float rotation) noexcept
{
    m_y_rotation = rotation;
}

void Core::Resources::Map::MapObject::setZRotation(float rotation) noexcept
{
    m_z_rotation = rotation;
}

void Core::Resources::Map::MapObject::setPosition(const bg::point3f_t& position) noexcept
{
    m_position = position;
}

float Core::Resources::Map::MapObject::getScale() const noexcept
{
    return m_scale;
}

float Core::Resources::Map::MapObject::getXRotation() const noexcept
{
    return m_x_rotation;
}

float Core::Resources::Map::MapObject::getYRotation() const noexcept
{
    return m_y_rotation;
}

float Core::Resources::Map::MapObject::getZRotation() const noexcept
{
    return m_z_rotation;
}

const bg::point3f_t& Core::Resources::Map::MapObject::getPosition() const noexcept
{
    return m_position;
}

#pragma endregion

#pragma region Map

void Core::Resources::Map::setDimensions(const bg::box2f_t& dimensions) noexcept
{
    m_map_dimensions = dimensions;
}

void Core::Resources::Map::setTreeModelsName(const std::string& model_name)
{
    m_tree_models_name = model_name;
}

void Core::Resources::Map::setHouseModelsName(const std::string& model_name)
{
    m_house_models_name = model_name;
}

void Core::Resources::Map::setGroundModelsName(const std::string& model_name)
{
    m_ground_models_name = model_name;
}

void Core::Resources::Map::setTreeObjects(std::vector<MapObject>&& map_objects) noexcept
{
    m_tree_objects = std::move(map_objects);
}

void Core::Resources::Map::setHouseObjects(std::vector<MapObject>&& map_objects) noexcept
{
    m_house_objects = std::move(map_objects);
}

void Core::Resources::Map::setGroundObjects(std::vector<MapObject>&& map_objects) noexcept
{
    m_ground_objects = std::move(map_objects);
}

const bg::box2f_t& Core::Resources::Map::getDimensions() const noexcept
{
    return m_map_dimensions;
}

std::string_view Core::Resources::Map::getTreeModelsName() const noexcept
{
    return m_tree_models_name;
}

std::string_view Core::Resources::Map::getHouseModelsName() const noexcept
{
    return m_house_models_name;
}

std::string_view Core::Resources::Map::getGroundModelsName() const noexcept
{
    return m_ground_models_name;
}

const std::vector<Core::Resources::Map::MapObject>& Core::Resources::Map::getTreeObjects() const noexcept
{
    return m_tree_objects;
}

const std::vector<Core::Resources::Map::MapObject>& Core::Resources::Map::getHouseObjects() const noexcept
{
    return m_house_objects;
}

const std::vector<Core::Resources::Map::MapObject>& Core::Resources::Map::getGroundObjects() const noexcept
{
    return m_ground_objects;
}

bool Core::Resources::Map::load(std::string_view map_path) noexcept
{
    return Loaders::MapLoader::load(*this, map_path);
}

#pragma endregion
