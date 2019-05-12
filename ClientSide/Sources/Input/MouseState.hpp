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

#include "../Utils/Debug.hpp"
#include "../Utils/Configuration.hpp"

namespace Input {

    class MouseState 
    {
    public:
        explicit MouseState() noexcept;
        void setPosition(int x_pos, int y_pos) noexcept;
        int getAndUnsetXDisplacementOffset() noexcept;
        int getAndUnsetYDisplacementOffset() noexcept;
        void setWheelOffset(int value) noexcept;
        int getAndUnsetWheelOffset() noexcept;
        void pressLeftButton() noexcept;
        void releaseLeftButton() noexcept;
        void pressRightButton() noexcept;
        void releaseRightButton() noexcept;
        bool isPressedLeftButton() const noexcept;
        bool isPressedRightButton() const noexcept;
    private:
        std::atomic_int m_wheel_offset = 0;
        std::atomic_int m_x_position = 0;
        std::atomic_int m_y_position = 0;
        std::atomic_int m_last_x_position = Configuration::Window::window_width / 2;
        std::atomic_int m_last_y_position = Configuration::Window::window_height / 2;
        std::atomic_bool m_is_pressed_left_button = false;
        std::atomic_bool m_is_pressed_right_button = false;
    };

}
