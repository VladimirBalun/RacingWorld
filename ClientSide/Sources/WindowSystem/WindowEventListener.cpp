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

#include "WindowEventListener.hpp"

WindowSystem::WindowEventListener& WindowSystem::WindowEventListener::getInstance() noexcept
{
    static WindowEventListener window_event_listener;
    return window_event_listener;
}

Input::KeyboardState& WindowSystem::WindowEventListener::getKeyboardState() noexcept
{
    return m_keyboard_state;
}

Input::MouseState& WindowSystem::WindowEventListener::getMouseState() noexcept
{
    return m_mouse_state;
}

 LRESULT CALLBACK WindowSystem::WindowEventListener::onWindowEvent(HWND window_handle, std::size_t window_event, WPARAM w_param, LPARAM l_param) noexcept
 {
     return getInstance().handleWindowEvent(window_handle, window_event, w_param, l_param);
 }

LRESULT CALLBACK WindowSystem::WindowEventListener::handleWindowEvent(HWND window_handle, std::size_t window_event, WPARAM w_param, LPARAM l_param) noexcept
{
    switch (window_event)
    {
    case WM_KEYDOWN:
        onKeyboardKeyDownEvent(w_param);
        break;
    case WM_KEYUP:
        onKeyboardKeyUpEvent(w_param);
        break;
    case WM_MOUSEWHEEL:
        onMouseWheelEvent(w_param);
        break;
    case WM_MOUSEMOVE:
        onMouseMoveEvent(l_param);
        break;
    case WM_LBUTTONDOWN:
        onMouseLeftBtnDownEvent(l_param);
        break;
    case WM_RBUTTONDOWN:
        onMouseRightBtnDownEvent(l_param);
        break;
    case WM_LBUTTONUP:
        onMouseLeftBtnUpEvent(l_param);
        break;
    case WM_RBUTTONUP:
        onMouseRightBtnUpEvent(l_param);
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(window_handle, (UINT)window_event, w_param, l_param);
    }

    return 0;
}

void WindowSystem::WindowEventListener::onKeyboardKeyDownEvent(WPARAM w_param) noexcept
{
    switch (w_param)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case Input::VK_W:
        m_keyboard_state.pressKeyW();
        break;
    case Input::VK_S:
        m_keyboard_state.pressKeyS();
        break;
    case Input::VK_A:
        m_keyboard_state.pressKeyA();
        break;
    case Input::VK_D:
        m_keyboard_state.pressKeyD();
        break;
    }
}

void WindowSystem::WindowEventListener::onKeyboardKeyUpEvent(WPARAM w_param) noexcept
{
    switch (w_param)
    {
    case Input::VK_W:
        m_keyboard_state.releaseKeyW();
        break;
    case Input::VK_S:
        m_keyboard_state.releaseKeyS();
        break;
    case Input::VK_A:
        m_keyboard_state.releaseKeyA();
        break;
    case Input::VK_D:
        m_keyboard_state.releaseKeyD();
        break;
    }
}

void WindowSystem::WindowEventListener::onMouseWheelEvent(LPARAM l_param) noexcept
{
    static std::uint8_t wheel_offset = 1;
    if (l_param > 0)
        m_mouse_state.setWheelOffset(-wheel_offset);
    else
        m_mouse_state.setWheelOffset(wheel_offset);
}

void WindowSystem::WindowEventListener::onMouseMoveEvent(LPARAM l_param) noexcept
{
    const INT x_pos = LOWORD(l_param);
    const INT y_pos = HIWORD(l_param);
    m_mouse_state.setPosition(x_pos, y_pos);
}

void WindowSystem::WindowEventListener::onMouseLeftBtnDownEvent(LPARAM l_param) noexcept
{
    m_mouse_state.pressLeftButton();
}

void WindowSystem::WindowEventListener::onMouseRightBtnDownEvent(LPARAM l_param) noexcept
{
    m_mouse_state.pressRightButton();
}

void WindowSystem::WindowEventListener::onMouseLeftBtnUpEvent(LPARAM l_param) noexcept
{
    m_mouse_state.releaseLeftButton();
}

void WindowSystem::WindowEventListener::onMouseRightBtnUpEvent(LPARAM l_param) noexcept
{
    m_mouse_state.releaseRightButton();
}
