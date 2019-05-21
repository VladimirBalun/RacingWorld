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

#include "WindowEventListener.hpp"
#include "../EventSystem/EventManager.hpp"
#include "../Graphics/SceneGraph/Scene.hpp"

namespace WindowSystem {

    class Window : public EventSystem::IEventSubscriber
    {
    public:
        explicit Window(HINSTANCE& app_instance, int cmd_show) noexcept;
        void showWindow(LPCSTR window_title, bool full_screen = false) noexcept;
        void onEvent(const char* message) const noexcept override;
        ~Window();
    private:
        void initOpenGLContext() noexcept;
        void initFullScreen(DWORD window_width, DWORD window_height, DWORD window_bpp) noexcept;
    private:
        int m_cmd_show;
        MSG m_window_event;
        HWND m_window_handle;
        HDC m_window_context;
        HGLRC m_opengl_context;
        HINSTANCE& m_app_instance;
        WNDCLASSEX m_window_class;
    };

}
