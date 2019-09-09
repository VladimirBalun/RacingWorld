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

#include <atomic>
#include <GLFW/glfw3.h>

#include "../Helpers/Holders/Singleton.hpp"

#ifndef g_mouse_state
    #define g_mouse_state Core::Input::MouseState::getInstance()
#endif // g_mouse_state

namespace Core { namespace Input {

    class MouseState : public Helpers::Holders::Singleton<MouseState>
    {
        friend void onMouseMoveEvent(GLFWwindow*, double, double) noexcept;
    public:
        int getAndUnsetWheelOffset() noexcept;
        bool isPressedLeftButton() const noexcept;
        bool isPressedRightButton() const noexcept;
        int getAndUnsetXDisplacementOffset() noexcept;
        int getAndUnsetYDisplacementOffset() noexcept;
    private:
        void pressLeftButton() noexcept;
        void pressRightButton() noexcept;
        void releaseLeftButton() noexcept;
        void releaseRightButton() noexcept;
        void setWheelOffset(int value) noexcept;
        void setPosition(int x_pos, int y_pos) noexcept;
    private:
        std::atomic_int m_wheel_offset = 0;
        std::atomic_int m_x_position = 0;
        std::atomic_int m_y_position = 0;
        std::atomic_int m_last_x_position = 430; // window_width / 2
        std::atomic_int m_last_y_position = 300; // window_height / 2
        std::atomic_bool m_is_pressed_left_button = false;
        std::atomic_bool m_is_pressed_right_button = false;
    };

}}
