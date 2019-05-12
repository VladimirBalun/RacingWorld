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

#include "Camera.hpp"

GLvoid Graphics::SceneGraph::Camera::setSpeed(GLfloat speed) noexcept
{
    m_speed = speed / 1000;
}

GLvoid Graphics::SceneGraph::Camera::moveLeft() noexcept
{
    Math::Vector3f right_direction = Math::cross(m_forward_direction, m_up_direction);
    right_direction.normalize();
    right_direction.mul(m_speed);
    m_position.sub(right_direction);
}

GLvoid Graphics::SceneGraph::Camera::moveRight() noexcept
{
    Math::Vector3f right_direction = Math::cross(m_forward_direction, m_up_direction);
    right_direction.normalize();
    right_direction.mul(m_speed);
    m_position.add(right_direction);
}

GLvoid Graphics::SceneGraph::Camera::moveForward() noexcept
{
    m_position.add(m_forward_direction * m_speed);
}

GLvoid Graphics::SceneGraph::Camera::moveBackward() noexcept
{
    m_position.sub(m_forward_direction * m_speed);
}

GLvoid Graphics::SceneGraph::Camera::turn(GLint x_offset, GLint y_offset) noexcept
{
    static const GLfloat sensitivity = 0.05f;
    m_yaw_angle += x_offset * sensitivity;
    m_pitch_angle += y_offset * sensitivity;

    if (m_pitch_angle > 89.0f)
        m_pitch_angle = 89.0f;
    if (m_pitch_angle < -89.0f)
        m_pitch_angle = -89.0f;

    const GLfloat pitch_angle_per_radians = Math::radians(m_pitch_angle);
    const GLfloat yaw_angle_per_radians = Math::radians(m_yaw_angle);
    const GLfloat pitch_angle_cosine = cos(pitch_angle_per_radians);
    m_forward_direction.setX(pitch_angle_cosine * cos(yaw_angle_per_radians));
    m_forward_direction.setY(sin(pitch_angle_per_radians));
    m_forward_direction.setZ(pitch_angle_cosine * sin(yaw_angle_per_radians));
    m_forward_direction.normalize();
}

GLvoid Graphics::SceneGraph::Camera::scale(GLint value) noexcept
{
    const static float FOV_MIN_SIZE = 15.0f;
    const static float FOW_MAX_SIZE = 45.0f;

    m_fov += value;
    if (m_fov < FOV_MIN_SIZE)
        m_fov = FOV_MIN_SIZE;
    if (m_fov > FOW_MAX_SIZE)
        m_fov = FOW_MAX_SIZE;
}

const Math::Vector3f& Graphics::SceneGraph::Camera::getPosition() const noexcept
{
    return m_position;
}

const Math::Matrix4x4f& Graphics::SceneGraph::Camera::getViewMatrix() const noexcept
{
    static Math::Matrix4x4f view_matrix;
    Math::setLookAt(view_matrix, m_position, m_position + m_forward_direction, m_up_direction);
    return view_matrix;
}

const Math::Matrix4x4f& Graphics::SceneGraph::Camera::getProjectionMatrix() const noexcept
{
    static Math::Matrix4x4f perspective_matrix{};
    const std::uint16_t window_width = Configuration::Window::window_width;
    const std::uint16_t window_height = Configuration::Window::window_height;
    Math::setPerspectiveMatrix(perspective_matrix, m_fov, static_cast<GLfloat>(window_width / window_height), 0.1f, 100.f);
    return perspective_matrix;
}
