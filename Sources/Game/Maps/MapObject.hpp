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

namespace Game::Maps
{

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

}
