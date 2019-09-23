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
#include "MouseState.hpp"

int Core::Input::MouseState::getAndUnsetWheelOffset() noexcept
{
    const int offset = m_wheel_offset.load();
    m_wheel_offset.store(0);
    return offset;
}

bool Core::Input::MouseState::isPressedLeftButton() const noexcept
{
    return m_is_pressed_left_button.load();
}

bool Core::Input::MouseState::isPressedRightButton() const noexcept
{
    return m_is_pressed_right_button.load();
}

int Core::Input::MouseState::getAndUnsetXDisplacementOffset() noexcept
{
    const int offset = m_x_position.load() - m_last_x_position.load();
    m_last_x_position.store(m_x_position);
    return offset;
}

int Core::Input::MouseState::getAndUnsetYDisplacementOffset() noexcept
{
    const int offset = m_last_y_position.load() - m_y_position.load();
    m_last_y_position.store(m_y_position);
    return offset;
}

void Core::Input::MouseState::pressLeftButton() noexcept
{
    m_is_pressed_left_button.store(true);
}

void Core::Input::MouseState::pressRightButton() noexcept
{
    m_is_pressed_right_button.store(true);
}

void Core::Input::MouseState::releaseLeftButton() noexcept
{
    m_is_pressed_left_button.store(false);
}

void Core::Input::MouseState::releaseRightButton() noexcept
{
    m_is_pressed_right_button.store(false);
}

void Core::Input::MouseState::setWheelOffset(const int value) noexcept
{
    m_wheel_offset.fetch_add(value);
}

void Core::Input::MouseState::setPosition(const int x_pos, const int y_pos) noexcept
{
    m_last_x_position.store(m_x_position);
    m_last_y_position.store(m_y_position);
    m_x_position.store(x_pos);
    m_y_position.store(y_pos);
}
