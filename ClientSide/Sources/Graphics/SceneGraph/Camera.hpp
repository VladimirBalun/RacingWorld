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

#include "../OpenGL.hpp"
#include "../../Math/Math.hpp"
#include "../../Utils/Configuration.hpp"

namespace Graphics { namespace SceneGraph {

    class Camera 
    {
    public:
        GLvoid moveLeft() noexcept;
        GLvoid moveRight() noexcept;
        GLvoid moveForward() noexcept;
        GLvoid moveBackward() noexcept;
        GLvoid setSpeed(GLfloat speed) noexcept;
        GLvoid turn(GLint x_offset, GLint y_offset) noexcept;
        GLvoid scale(GLint value) noexcept;
        const Math::Vector3f& getPosition() const noexcept;
        const Math::Matrix4x4f& getViewMatrix() const noexcept;
        const Math::Matrix4x4f& getProjectionMatrix() const noexcept;
    private:
        GLfloat m_speed = 0.0f;
        GLfloat m_fov = 45.0f;
        GLfloat m_yaw_angle = -90.0f;
        GLfloat m_pitch_angle = 0.0f;
        Math::Vector3f m_position = { 0.0f, 0.0f, 3.0f };
        Math::Vector3f m_up_direction = { 0.0f, 1.0f, 0.0f };
        Math::Vector3f m_forward_direction = { 0.0f, 0.0f, -1.0f };
    };

} }
