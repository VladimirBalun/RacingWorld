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

#ifndef g_keyboard_state
    #define g_keyboard_state Core::Input::KeyboardState::getInstance()
#endif // g_keyboard_state

namespace Core::Input 
{

    class KeyboardState : public Helpers::Holders::Singleton<KeyboardState>
    {
        friend void onMouseClickEvent(GLFWwindow*, int, int, int) noexcept;
        friend void onKeyboardEvent(GLFWwindow*, int, int, int, int) noexcept;
    public:
        bool isPressedKeyW() const noexcept;
        bool isPressedKeyS() const noexcept;
        bool isPressedKeyA() const noexcept;
        bool isPressedKeyD() const noexcept;
    private:
        void pressKeyW() noexcept;
        void pressKeyS() noexcept;
        void pressKeyA() noexcept;
        void pressKeyD() noexcept;
        void releaseKeyW() noexcept;
        void releaseKeyS() noexcept;
        void releaseKeyA() noexcept;
        void releaseKeyD() noexcept;
    private:
        std::atomic_bool m_is_pressed_key_w = false;
        std::atomic_bool m_is_pressed_key_s = false;
        std::atomic_bool m_is_pressed_key_a = false;
        std::atomic_bool m_is_pressed_key_d = false;
    };

}
