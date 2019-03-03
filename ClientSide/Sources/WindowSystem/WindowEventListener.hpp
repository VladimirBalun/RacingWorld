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
        static WindowEventListener& getInstance();
        static LRESULT CALLBACK onWindowEvent(HWND windowHandle, std::size_t windowEvent, WPARAM wParam, LPARAM lParam) noexcept;
        Input::KeyboardState& getKeyboardState() noexcept;
        Input::MouseState& getMouseState() noexcept;
    private:
        LRESULT CALLBACK handleWindowEvent(HWND windowHandle, std::size_t windowEvent, WPARAM wParam, LPARAM lParam) noexcept;
        void onKeyboardKeyDownEvent(WPARAM wParam) noexcept;
        void onKeyboardKeyUpEvent(WPARAM wParam) noexcept;
        void onMouseWheelEvent(LPARAM lParam) noexcept;
        void onMouseMoveEvent(LPARAM lParam) noexcept;
        void onMouseLeftBtnUpEvent(LPARAM lParam) noexcept;
        void onMouseRightBtnUpEvent(LPARAM lParam) noexcept;
        void onMouseLeftBtnDownEvent(LPARAM lParam) noexcept;
        void onMouseRightBtnDownEvent(LPARAM lParam) noexcept;
    private:
        Input::MouseState mMouseState;
        Input::KeyboardState mKeyboardState;
    };

}
