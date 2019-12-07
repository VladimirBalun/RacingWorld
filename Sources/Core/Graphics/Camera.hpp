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

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Graphics
{

    class Camera
    {
    public:
        void moveLeft() noexcept;
        void moveRight() noexcept;
        void moveForward() noexcept;
        void moveBackward() noexcept;
        void setSpeed(float speed) noexcept;
        void turn(int x_offset, int y_offset) noexcept;
        const glm::vec3& getPosition() const noexcept;
        glm::mat4x4 getViewMatrix() const noexcept;
        glm::mat4x4 getProjectionMatrix() const noexcept;
    private:
        float m_speed = 0.0f;
        float m_fov = 45.0f;
        float m_yaw_angle = -90.0f;
        float m_pitch_angle = 0.0f;
        glm::vec3 m_position{ 0.0f, 0.0f, 3.0f };
        glm::vec3 m_up_direction{ 0.0f, 1.0f, 0.0f };
        glm::vec3 m_forward_direction{ 0.0f, 0.0f, -1.0f };
    };

}
