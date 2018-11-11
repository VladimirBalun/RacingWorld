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

LRESULT CALLBACK Platforms::WindowSystem::on_window_event(HWND window_handle, UINT window_event, WPARAM w_param, LPARAM l_param) noexcept
{
    switch (window_event)
    {

    case WM_KEYDOWN:
        _on_keyboard_key_down_event(w_param);
        break;
    case WM_KEYUP:
        _on_keyboard_key_up_event(w_param);
        break;

    case WM_CLOSE:
    {
        PostQuitMessage(0);
    }
    break;

    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;

    default:
    {
        return DefWindowProc(window_handle, window_event, w_param, l_param);
    }
    break;

    }

    return 0;
}

VOID Platforms::WindowSystem::_on_keyboard_key_down_event(WPARAM w_param) noexcept
{
    switch (w_param)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    }
}

VOID Platforms::WindowSystem::_on_keyboard_key_up_event(WPARAM w_param) noexcept
{
    switch (w_param)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    }
}

VOID Platforms::WindowSystem::_on_mouse_event() noexcept
{

}
