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

#include <cstdint>
#include <cstdlib>
#include <Windows.h>

#include "../Input/MouseState.hpp"
#include "../Input/KeyboardState.hpp"
#include "../Input/EKeyboardCode.hpp"

namespace WindowSystem {

    // Singleton
    class WindowEventListener 
    {
        WindowEventListener() = default;
        ~WindowEventListener() = default;
        WindowEventListener(const WindowEventListener&) = delete;
        WindowEventListener& operator = (const WindowEventListener&) = delete;
    public:
        static WindowEventListener& getInstance() noexcept;
        static LRESULT CALLBACK onWindowEvent(HWND window_handle, std::size_t window_event, WPARAM w_param, LPARAM l_param) noexcept;
        Input::KeyboardState& getKeyboardState() noexcept;
        Input::MouseState& getMouseState() noexcept;
    private:
        LRESULT CALLBACK handleWindowEvent(HWND window_handle, std::size_t window_event, WPARAM w_param, LPARAM l_param) noexcept;
        void onKeyboardKeyDownEvent(WPARAM w_param) noexcept;
        void onKeyboardKeyUpEvent(WPARAM w_param) noexcept;
        void onMouseWheelEvent(LPARAM l_param) noexcept;
        void onMouseMoveEvent(LPARAM l_param) noexcept;
        void onMouseLeftBtnUpEvent(LPARAM l_param) noexcept;
        void onMouseRightBtnUpEvent(LPARAM l_param) noexcept;
        void onMouseLeftBtnDownEvent(LPARAM l_param) noexcept;
        void onMouseRightBtnDownEvent(LPARAM l_param) noexcept;
    private:
        Input::MouseState m_mouse_state{};
        Input::KeyboardState m_keyboard_state{};
    };

}
