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

#include "WindowEventListener.h"

Platforms::WindowSystem::WindowEventListener& Platforms::WindowSystem::WindowEventListener::getInstance()
{
    static WindowEventListener windowEventListener;
    return windowEventListener;
}

Platforms::KeyboardState& Platforms::WindowSystem::WindowEventListener::getKeyboardState() noexcept
{
    return _keyboardState;
}

Platforms::MouseState& Platforms::WindowSystem::WindowEventListener::getMouseState() noexcept
{
    return _mouseState;
}

 LRESULT CALLBACK Platforms::WindowSystem::WindowEventListener::onWindowEvent(HWND windowHandle, UINT windowEvent, WPARAM wParam, LPARAM lParam) noexcept
 {
     return getInstance().handleWindowEvent(windowHandle, windowEvent, wParam, lParam);
 }

LRESULT CALLBACK Platforms::WindowSystem::WindowEventListener::handleWindowEvent(HWND windowHandle, UINT windowEvent, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (windowEvent)
    {
    case WM_KEYDOWN:
        onKeyboardKeyDownEvent(wParam);
        break;
    case WM_KEYUP:
        onKeyboardKeyUpEvent(wParam);
        break;
    case WM_MOUSEMOVE:
        onMouseMoveEvent(lParam);
        break;
    case WM_LBUTTONDOWN:
        onMouseLeftBtnDownEvent(lParam);
        break;
    case WM_RBUTTONDOWN:
        onMouseRightBtnDownEvent(lParam);
        break;
    case WM_LBUTTONUP:
        onMouseLeftBtnUpEvent(lParam);
        break;
    case WM_RBUTTONUP:
        onMouseRightBtnUpEvent(lParam);
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(windowHandle, windowEvent, wParam, lParam);
    }

    return 0;
}

VOID Platforms::WindowSystem::WindowEventListener::onKeyboardKeyDownEvent(WPARAM wParam) noexcept
{
    switch (wParam)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case VK_W:
        _keyboardState.pressKeyW();
        break;
    case VK_S:
        _keyboardState.pressKeyS();
        break;
    case VK_A:
        _keyboardState.pressKeyA();
        break;
    case VK_D:
        _keyboardState.pressKeyD();
        break;
    }
}

VOID Platforms::WindowSystem::WindowEventListener::onKeyboardKeyUpEvent(WPARAM wParam) noexcept
{
    switch (wParam)
    {
    case VK_W:
        _keyboardState.releaseKeyW();
        break;
    case VK_S:
        _keyboardState.releaseKeyS();
        break;
    case VK_A:
        _keyboardState.releaseKeyA();
        break;
    case VK_D:
        _keyboardState.releaseKeyD();
        break;
    }
}

VOID Platforms::WindowSystem::WindowEventListener::onMouseMoveEvent(LPARAM lParam) noexcept
{
    const INT x_pos = LOWORD(lParam);
    const INT y_pos = HIWORD(lParam);
}

VOID Platforms::WindowSystem::WindowEventListener::onMouseLeftBtnDownEvent(LPARAM lParam) noexcept
{
    _mouseState.pressLeftButton();
}

VOID Platforms::WindowSystem::WindowEventListener::onMouseRightBtnDownEvent(LPARAM lParam) noexcept
{
    _mouseState.pressRightButton();
}

VOID Platforms::WindowSystem::WindowEventListener::onMouseLeftBtnUpEvent(LPARAM lParam) noexcept
{
    _mouseState.releaseLeftButton();
}

VOID Platforms::WindowSystem::WindowEventListener::onMouseRightBtnUpEvent(LPARAM lParam) noexcept
{
    _mouseState.releaseRightButton();
}
