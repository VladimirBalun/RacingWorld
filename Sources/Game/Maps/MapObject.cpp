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
#include "MapObject.hpp"

void Game::Maps::MapObject::setScale(float scale) noexcept
{
    m_scale = scale;
}

void Game::Maps::MapObject::setXRotation(float rotation) noexcept
{
    m_x_rotation = rotation;
}

void Game::Maps::MapObject::setYRotation(float rotation) noexcept
{
    m_y_rotation = rotation;
}

void Game::Maps::MapObject::setZRotation(float rotation) noexcept
{
    m_z_rotation = rotation;
}

void Game::Maps::MapObject::setPosition(const bg::point3f_t& position) noexcept
{
    m_position = position;
}

float Game::Maps::MapObject::getScale() const noexcept
{
    return m_scale;
}

float Game::Maps::MapObject::getXRotation() const noexcept
{
    return m_x_rotation;
}

float Game::Maps::MapObject::getYRotation() const noexcept
{
    return m_y_rotation;
}

float Game::Maps::MapObject::getZRotation() const noexcept
{
    return m_z_rotation;
}

const bg::point3f_t& Game::Maps::MapObject::getPosition() const noexcept
{
    return m_position;
}
