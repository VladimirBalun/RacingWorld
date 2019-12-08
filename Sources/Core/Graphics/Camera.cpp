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
#include "Camera.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.inl>
#include <glm/ext/matrix_clip_space.inl>
#include <glm/detail/func_trigonometric.inl>

void Core::Graphics::Camera::setSpeed(GLfloat speed) noexcept
{
    m_speed = speed / 1000;
}

void Core::Graphics::Camera::moveLeft() noexcept
{
    glm::vec3 right_direction = cross(m_forward_direction, m_up_direction);
    normalize(right_direction);
    right_direction *= m_speed;
    m_position -= right_direction;
}

void Core::Graphics::Camera::moveRight() noexcept
{
    glm::vec3 right_direction = cross(m_forward_direction, m_up_direction);
    normalize(right_direction);
    right_direction *= m_speed;
    m_position += right_direction;
}

void Core::Graphics::Camera::moveForward() noexcept
{
    m_position += m_forward_direction * m_speed;
}

void Core::Graphics::Camera::moveBackward() noexcept
{
    m_position -= m_forward_direction * m_speed;
}

void Core::Graphics::Camera::turn(GLint x_offset, GLint y_offset) noexcept
{
    constexpr float SENSIIVITY = 0.05f;
    constexpr float PITCH_MIN_ANGLE = -89.0f;
    constexpr float PITCH_MAX_ANGLE = 89.0f;

    m_yaw_angle += x_offset * SENSIIVITY;
    m_pitch_angle += y_offset * SENSIIVITY;

    if (m_pitch_angle > PITCH_MAX_ANGLE) 
    {
        m_pitch_angle = PITCH_MAX_ANGLE;
    }
    if (m_pitch_angle < PITCH_MIN_ANGLE) 
    {
        m_pitch_angle = PITCH_MIN_ANGLE;
    }

    const float pitch_angle_per_radians = glm::radians(m_pitch_angle);
    const float yaw_angle_per_radians = glm::radians(m_yaw_angle);
    const float pitch_angle_cosine = cos(pitch_angle_per_radians);
    m_forward_direction.x = pitch_angle_cosine * cos(yaw_angle_per_radians);
    m_forward_direction.y = sin(pitch_angle_per_radians);
    m_forward_direction.z  = pitch_angle_cosine * sin(yaw_angle_per_radians);
    normalize(m_forward_direction);
}

const glm::vec3& Core::Graphics::Camera::getPosition() const noexcept
{
    return m_position;
}

glm::mat4x4 Core::Graphics::Camera::getViewMatrix() const noexcept
{
    return lookAt(m_position, m_position + m_forward_direction, m_up_direction);;
}

glm::mat4x4 Core::Graphics::Camera::getProjectionMatrix() const noexcept
{
    glm::mat4x4 perspective_matrix{ 1.0f };
    const int window_width = 860;  // TODO
    const int window_height = 600; // TODO
    perspective_matrix = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
    return perspective_matrix;
}
