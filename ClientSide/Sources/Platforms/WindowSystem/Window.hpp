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
#include "../../Graphics/OpenGL4.hpp"
#include "../../Graphics/SceneGraph.hpp"
#include "../../Utils/Logger.hpp"

namespace Platforms { namespace WindowSystem {

    class Window
    {
    public:
        explicit Window(HINSTANCE& appInstance, INT cmdShow);
        VOID showWindow(LPCSTR windowTitle, INT windowWidth, INT windowHeight);
        ~Window();
    private:
        VOID initWindowContext();
    private:
        INT _cmdShow;
        MSG _windowEvent;
        HWND _windowHandle;
        HDC _windowContext;
        HGLRC _openGLContext;
        HINSTANCE& _appInstance;
        WNDCLASSEX _windowClass;
        LPCSTR _windowClassName;
    };

} }
