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

void Game::Maps::Map::setDimensions(const bg::box2f_t& dimensions) noexcept
{
    m_map_dimensions = dimensions;
}

void Game::Maps::Map::setTreeModelsName(const std::string& model_name)
{
    m_tree_models_name = model_name;
}

void Game::Maps::Map::setHouseModelsName(const std::string& model_name)
{
    m_house_models_name = model_name;
}

void Game::Maps::Map::setGroundModelsName(const std::string& model_name)
{
    m_ground_models_name = model_name;
}

void Game::Maps::Map::setTreeObjects(std::vector<MapObject>&& map_objects) noexcept
{
    m_tree_objects = std::move(map_objects);
}

void Game::Maps::Map::setHouseObjects(std::vector<MapObject>&& map_objects) noexcept
{
    m_house_objects = std::move(map_objects);
}

void Game::Maps::Map::setGroundObjects(std::vector<MapObject>&& map_objects) noexcept
{
    m_ground_objects = std::move(map_objects);
}

const bg::box2f_t& Game::Maps::Map::getDimensions() const noexcept
{
    return m_map_dimensions;
}

std::string_view Game::Maps::Map::getTreeModelsName() const noexcept
{
    return m_tree_models_name;
}

std::string_view Game::Maps::Map::getHouseModelsName() const noexcept
{
    return m_house_models_name;
}

std::string_view Game::Maps::Map::getGroundModelsName() const noexcept
{
    return m_ground_models_name;
}

const std::vector<Game::Maps::MapObject>& Game::Maps::Map::getTreeObjects() const noexcept
{
    return m_tree_objects;
}

const std::vector<Game::Maps::MapObject>& Game::Maps::Map::getHouseObjects() const noexcept
{
    return m_house_objects;
}

const std::vector<Game::Maps::MapObject>& Game::Maps::Map::getGroundObjects() const noexcept
{
    return m_ground_objects;
}
