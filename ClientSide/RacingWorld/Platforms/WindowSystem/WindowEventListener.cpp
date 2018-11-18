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
        on_keyboard_key_down_event(w_param);
        break;
    case WM_KEYUP:
        on_keyboard_key_up_event(w_param);
        break;
    case WM_MOUSEMOVE:
        on_mouse_move_event(l_param);
        break;
    case WM_LBUTTONDOWN:
        on_mouse_left_btn_click_event(l_param);
        break;
    case WM_RBUTTONDOWN:
        on_mouse_right_btn_click_event(l_param);
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(window_handle, window_event, w_param, l_param);
    }

    return 0;
}

VOID Platforms::WindowSystem::on_keyboard_key_down_event(WPARAM w_param) noexcept
{
    switch (w_param)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case VK_SPACE:
        break;
    case VK_W:
        break;
    case VK_S:
        break;
    case VK_A:
        break;
    case VK_D:
        break;
    }
}

VOID Platforms::WindowSystem::on_keyboard_key_up_event(WPARAM w_param) noexcept
{
    switch (w_param)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case VK_SPACE:
        break;
    case VK_W:
        break;
    case VK_S:
        break;
    case VK_A:
        break;
    case VK_D:
        break;
    }
}

VOID Platforms::WindowSystem::on_mouse_move_event(LPARAM l_param) noexcept
{
    INT x_pos = LOWORD(l_param);
    INT y_pos = HIWORD(l_param);
}

VOID Platforms::WindowSystem::on_mouse_left_btn_click_event(LPARAM l_param) noexcept
{
    INT x_pos = LOWORD(l_param);
    INT y_pos = HIWORD(l_param);
}

VOID Platforms::WindowSystem::on_mouse_right_btn_click_event(LPARAM l_param) noexcept
{
    INT x_pos = LOWORD(l_param);
    INT y_pos = HIWORD(l_param);
}
