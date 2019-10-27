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

#define FOV_MIN_SIZE    15.0f
#define FOW_MAX_SIZE    45.0f
#define PITCH_MIN_ANGLE -89.0f
#define PITCH_MAX_ANGLE 89.0f

void Graphics::Camera::setSpeed(GLfloat speed) noexcept
{
    m_speed = speed / 1000;
}

void Graphics::Camera::moveLeft() noexcept
{
    glm::vec3 right_direction = cross(m_forward_direction, m_up_direction);
    normalize(right_direction);
    right_direction *= m_speed;
    m_position -= right_direction;
}

void Graphics::Camera::moveRight() noexcept
{
    glm::vec3 right_direction = cross(m_forward_direction, m_up_direction);
    normalize(right_direction);
    right_direction *= m_speed;
    m_position += right_direction;
}

void Graphics::Camera::moveForward() noexcept
{
    m_position += m_forward_direction * m_speed;
}

void Graphics::Camera::moveBackward() noexcept
{
    m_position -= m_forward_direction * m_speed;
}

void Graphics::Camera::turn(GLint x_offset, GLint y_offset) noexcept
{
    static const float sensitivity = 0.05f;
    m_yaw_angle += x_offset * sensitivity;
    m_pitch_angle += y_offset * sensitivity;

    if (m_pitch_angle > 89.0f)
        m_pitch_angle = 89.0f;
    if (m_pitch_angle < -89.0f)
        m_pitch_angle = -89.0f;

    const float pitch_angle_per_radians = glm::radians(m_pitch_angle);
    const float yaw_angle_per_radians = glm::radians(m_yaw_angle);
    const float pitch_angle_cosine = cos(pitch_angle_per_radians);
    m_forward_direction.x = pitch_angle_cosine * cos(yaw_angle_per_radians);
    m_forward_direction.y = sin(pitch_angle_per_radians);
    m_forward_direction.z  = pitch_angle_cosine * sin(yaw_angle_per_radians);
    normalize(m_forward_direction);
}

void Graphics::Camera::scale(GLint value) noexcept
{
    m_fov += value;
    if (m_fov < FOV_MIN_SIZE)
        m_fov = FOV_MIN_SIZE;
    if (m_fov > FOW_MAX_SIZE)
        m_fov = FOW_MAX_SIZE;
}

const glm::vec3& Graphics::Camera::getPosition() const noexcept
{
    return m_position;
}

glm::mat4x4 Graphics::Camera::getViewMatrix() const noexcept
{
    return lookAt(m_position, m_position + m_forward_direction, m_up_direction);
}

glm::mat4x4 Graphics::Camera::getProjectionMatrix() const noexcept
{
    glm::mat4x4 perspective_matrix{ 1.0f };
    const int window_width = 860;  // TODO
    const int window_height = 600; // TODO
    perspective_matrix = glm::perspective(m_fov, static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.f);
    return perspective_matrix;
}
