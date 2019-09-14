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

#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace Core { namespace GUI {
 
    class Window
    {
    public:
        Window(int width, int height, const std::string& title) noexcept;
        void show() noexcept;
        ~Window();
    private:
        void initGLContext() const noexcept;
        void initEventHandlers() const noexcept;
    private:
        GLFWwindow* m_window = nullptr;
    };

}}
