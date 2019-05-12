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

#include "MouseState.hpp"

Input::MouseState::MouseState() noexcept
{
#ifdef _DEBUG
    if (!m_x_position.is_lock_free() || !m_y_position.is_lock_free())
        LOG_WARNING("Operations with 'int' are not lock free on current platform.");
    if (!m_is_pressed_left_button.is_lock_free() || !m_is_pressed_right_button.is_lock_free())
        LOG_WARNING("Operations with 'bool' are not lock free on current platform.");
#endif // _DEBUG
}

void Input::MouseState::setPosition(int x_pos, int y_pos) noexcept
{
    m_last_x_position.store(m_x_position);
    m_last_y_position.store(m_y_position);
    m_x_position.store(x_pos);
    m_y_position.store(y_pos);
}

int Input::MouseState::getAndUnsetXDisplacementOffset() noexcept
{
    const int offset = m_x_position.load() - m_last_x_position.load();
    m_last_x_position.store(m_x_position);
    return offset;
}

int Input::MouseState::getAndUnsetYDisplacementOffset() noexcept
{
    const int offset = m_last_y_position.load() - m_y_position.load();
    m_last_y_position.store(m_y_position);
    return offset;
}

void Input::MouseState::setWheelOffset(int value) noexcept
{
    m_wheel_offset.fetch_add(value);
}

int Input::MouseState::getAndUnsetWheelOffset() noexcept
{
    const int offset = m_wheel_offset.load();
    m_wheel_offset.store(0);
    return offset;
}

void Input::MouseState::pressLeftButton() noexcept
{
    m_is_pressed_left_button.store(true);
}

void Input::MouseState::releaseLeftButton() noexcept
{
    m_is_pressed_left_button.store(false);
}

void Input::MouseState::pressRightButton() noexcept
{
    m_is_pressed_right_button.store(true);
}

void Input::MouseState::releaseRightButton() noexcept
{
    m_is_pressed_right_button.store(false);
}

bool Input::MouseState::isPressedLeftButton() const noexcept
{
    return m_is_pressed_left_button.load();
}

bool Input::MouseState::isPressedRightButton() const noexcept
{
    return m_is_pressed_right_button.load();
}
