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

#include <GLFW/glfw3.h>

namespace Core::Input 
{

    void onInputError(int error, const char* description) noexcept;
    void onMouseMoveEvent(GLFWwindow* window, double x_pos, double y_pos) noexcept;
    void onMouseClickEvent(GLFWwindow* window, int button, int action, int mods) noexcept;
    void onKeyboardEvent(GLFWwindow* window, int key, int scan_code, int action, int mods) noexcept;

}
