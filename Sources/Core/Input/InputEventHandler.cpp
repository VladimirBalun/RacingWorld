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

#include "PrecompiledHeader.hpp"
#include "InputEventHandler.hpp"

#include "MouseState.hpp"
#include "KeyboardState.hpp"
#include "../Helpers/Debug.hpp"
#include "../Helpers/Macroses.hpp"

void Core::Input::onInputError(const int error, const char* description) noexcept
{
    LOG_WARNING(STR("Input error:" + STR(description)));
}

void Core::Input::onMouseMoveEvent(GLFWwindow* window, double x_pos, double y_pos) noexcept
{
    g_mouse_state.setPosition(static_cast<int>(x_pos), static_cast<int>(y_pos));
}

void Core::Input::onMouseClickEvent(GLFWwindow* window, int button, int action, int mods) noexcept
{
    
}

void Core::Input::onKeyboardEvent(GLFWwindow* window, const int key, const int scan_code, const int action, const int mods) noexcept
{
    KeyboardState& keyboard_state = KeyboardState::getInstance();
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        keyboard_state.pressKeyW();
        return;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        keyboard_state.pressKeyS();
        return;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        keyboard_state.pressKeyA();
        return;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        keyboard_state.pressKeyD();
        return;
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        keyboard_state.releaseKeyW();
        return;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        keyboard_state.releaseKeyS();
        return;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        keyboard_state.releaseKeyA();
        return;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        keyboard_state.releaseKeyD();
    }
}
