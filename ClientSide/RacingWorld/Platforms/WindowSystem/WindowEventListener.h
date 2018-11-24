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

#include <Windows.h>

#include "../MouseState.h"
#include "../KeyboardState.h"
#include "../EWinKeyboardCode.h"

namespace Platforms { namespace WindowSystem {

    // Singleton
    class WindowEventListener 
    {
        WindowEventListener() = default;
        ~WindowEventListener() = default;
        WindowEventListener(const WindowEventListener& other) = delete; 
        WindowEventListener& operator = (const WindowEventListener& other) = delete;
    public:
        static WindowEventListener& getInstance();
        static LRESULT CALLBACK onWindowEvent(HWND windowHandle, UINT windowEvent, WPARAM wParam, LPARAM lParam) noexcept;
        KeyboardState& getKeyboardState() noexcept;
        MouseState& getMouseState() noexcept;
    private:
        LRESULT CALLBACK handleWindowEvent(HWND windowHandle, UINT windowEvent, WPARAM wParam, LPARAM lParam) noexcept;
        VOID onKeyboardKeyDownEvent(WPARAM w_param) noexcept;
        VOID onKeyboardKeyUpEvent(WPARAM w_param) noexcept;
        VOID onMouseMoveEvent(LPARAM l_param) noexcept;
        VOID onMouseLeftBtnUpEvent(LPARAM l_param) noexcept;
        VOID onMouseRightBtnUpEvent(LPARAM l_param) noexcept;
        VOID onMouseLeftBtnDownEvent(LPARAM l_param) noexcept;
        VOID onMouseRightBtnDownEvent(LPARAM l_param) noexcept;
    private:
        MouseState _mouseState;
        KeyboardState _keyboardState;
    };

} }
