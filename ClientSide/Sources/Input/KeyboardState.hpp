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

namespace Input {

    class KeyboardState
    {
    public:
        explicit KeyboardState() noexcept;
        void pressKeyW() noexcept;
        void releaseKeyW() noexcept;
        void pressKeyS() noexcept;
        void releaseKeyS() noexcept;
        void pressKeyA() noexcept;
        void releaseKeyA() noexcept;
        void pressKeyD() noexcept;
        void releaseKeyD() noexcept;
        bool isPressedKeyW() const noexcept;
        bool isPressedKeyS() const noexcept;
        bool isPressedKeyA() const noexcept;
        bool isPressedKeyD() const noexcept;
    private:
        std::atomic_bool m_is_pressed_key_w = false;
        std::atomic_bool m_is_pressed_key_s = false;
        std::atomic_bool m_is_pressed_key_a = false;
        std::atomic_bool m_is_pressed_key_d = false;
    };

}