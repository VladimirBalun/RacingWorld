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
    static WindowEventListener windowEventListener;
    return windowEventListener;
}

Input::KeyboardState& WindowSystem::WindowEventListener::getKeyboardState() noexcept
{
    return mKeyboardState;
}

Input::MouseState& WindowSystem::WindowEventListener::getMouseState() noexcept
{
    return mMouseState;
}

 LRESULT CALLBACK WindowSystem::WindowEventListener::onWindowEvent(HWND windowHandle, std::size_t windowEvent, WPARAM wParam, LPARAM lParam) noexcept
 {
     return getInstance().handleWindowEvent(windowHandle, windowEvent, wParam, lParam);
 }

LRESULT CALLBACK WindowSystem::WindowEventListener::handleWindowEvent(HWND windowHandle, std::size_t windowEvent, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (windowEvent)
    {
    case WM_KEYDOWN:
        onKeyboardKeyDownEvent(wParam);
        break;
    case WM_KEYUP:
        onKeyboardKeyUpEvent(wParam);
        break;
    case WM_MOUSEWHEEL:
        onMouseWheelEvent(wParam);
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
        return DefWindowProc(windowHandle, (UINT) windowEvent, wParam, lParam);
    }

    return 0;
}

void WindowSystem::WindowEventListener::onKeyboardKeyDownEvent(WPARAM wParam) noexcept
{
    switch (wParam)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case Input::VK_W:
        mKeyboardState.pressKeyW();
        break;
    case Input::VK_S:
        mKeyboardState.pressKeyS();
        break;
    case Input::VK_A:
        mKeyboardState.pressKeyA();
        break;
    case Input::VK_D:
        mKeyboardState.pressKeyD();
        break;
    }
}

void WindowSystem::WindowEventListener::onKeyboardKeyUpEvent(WPARAM wParam) noexcept
{
    switch (wParam)
    {
    case Input::VK_W:
        mKeyboardState.releaseKeyW();
        break;
    case Input::VK_S:
        mKeyboardState.releaseKeyS();
        break;
    case Input::VK_A:
        mKeyboardState.releaseKeyA();
        break;
    case Input::VK_D:
        mKeyboardState.releaseKeyD();
        break;
    }
}

void WindowSystem::WindowEventListener::onMouseWheelEvent(LPARAM lParam) noexcept
{
    static std::uint8_t wheelOffset = 1;
    if (lParam > 0)
        mMouseState.setWheelOffset(-wheelOffset);
    else
        mMouseState.setWheelOffset(wheelOffset);
}

void WindowSystem::WindowEventListener::onMouseMoveEvent(LPARAM lParam) noexcept
{
    const INT xPos = LOWORD(lParam);
    const INT yPos = HIWORD(lParam);
    mMouseState.setPosition(xPos, yPos);
}

void WindowSystem::WindowEventListener::onMouseLeftBtnDownEvent(LPARAM lParam) noexcept
{
    mMouseState.pressLeftButton();
}

void WindowSystem::WindowEventListener::onMouseRightBtnDownEvent(LPARAM lParam) noexcept
{
    mMouseState.pressRightButton();
}

void WindowSystem::WindowEventListener::onMouseLeftBtnUpEvent(LPARAM lParam) noexcept
{
    mMouseState.releaseLeftButton();
}

void WindowSystem::WindowEventListener::onMouseRightBtnUpEvent(LPARAM lParam) noexcept
{
    mMouseState.releaseRightButton();
}
