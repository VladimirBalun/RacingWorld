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

#include "KeyboardState.hpp"

Core::Input::KeyboardState& Core::Input::KeyboardState::getInstance() noexcept
{
    static KeyboardState instance{};
    return instance;
}

bool Core::Input::KeyboardState::isPressedKeyW() const noexcept
{
    return m_is_pressed_key_w.load();
}

bool Core::Input::KeyboardState::isPressedKeyS() const noexcept
{
    return m_is_pressed_key_s.load();
}

bool Core::Input::KeyboardState::isPressedKeyA() const noexcept
{
    return m_is_pressed_key_a.load();
}

bool Core::Input::KeyboardState::isPressedKeyD() const noexcept
{
    return m_is_pressed_key_d.load();
}

void Core::Input::KeyboardState::pressKeyW() noexcept
{
    m_is_pressed_key_w.store(true);
}

void Core::Input::KeyboardState::pressKeyS() noexcept
{
    m_is_pressed_key_s.store(true);
}

void Core::Input::KeyboardState::pressKeyA() noexcept
{
    m_is_pressed_key_a.store(true);
}

void Core::Input::KeyboardState::pressKeyD() noexcept
{
    m_is_pressed_key_d.store(true);
}

void Core::Input::KeyboardState::releaseKeyW() noexcept
{
    m_is_pressed_key_w.store(false);
}

void Core::Input::KeyboardState::releaseKeyS() noexcept
{
    m_is_pressed_key_s.store(false);
}

void Core::Input::KeyboardState::releaseKeyA() noexcept
{
    m_is_pressed_key_a.store(false);
}

void Core::Input::KeyboardState::releaseKeyD() noexcept
{
    m_is_pressed_key_d.store(false);
}
