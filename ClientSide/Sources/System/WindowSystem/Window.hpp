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

#include <WinSock2.h>

#include "WindowEventListener.hpp"
#include "../../Utils/Logger.hpp"
#include "../../Network/NetworkManager.hpp"
#include "../../Graphics/SceneGraph/Scene.hpp"

namespace Platforms { namespace WindowSystem {

    class Window
    {
    public:
        explicit Window(HINSTANCE& appInstance, int cmdShow);
        void showWindow(LPCSTR windowTitle, int windowWidth, int windowHeight, bool fullscreen = false);
        ~Window();
    private:
        void _initOpenGLContext();
        void _initFullscreen(DWORD windowWidth, DWORD windowHeight, DWORD windowBPP);
    private:
        int mCmdShow;
        DWORD dwStyle;
        DWORD dwExStyle;
        MSG mWindowEvent;
        HWND mWindowHandle;
        HDC mWindowContext;
        HGLRC mOpenGLContext;
        HINSTANCE& mAppInstance;
        WNDCLASSEX mWindowClass;
        LPCSTR mWindowClassName;
    };

} }
