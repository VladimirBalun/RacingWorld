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

#include <chrono>
#include <type_traits>

namespace Core { namespace Helpers {

    template<typename T>
    T getCurrentTimeInMinutes() noexcept
    {
        static_assert(std::is_arithmetic<T>::value, "Type of the time must be arithmetic.");
        const auto current_time = std::chrono::system_clock::now().time_since_epoch();
        return static_cast<T>(std::chrono::duration_cast<std::chrono::minutes>(current_time).count());
    }

    template<typename T>
    T getCurrentTimeInSeconds() noexcept
    {
        static_assert(std::is_arithmetic<T>::value, "Type of the time must be arithmetic.");
        const auto current_time = std::chrono::system_clock::now().time_since_epoch();
        return static_cast<T>(std::chrono::duration_cast<std::chrono::seconds>(current_time).count());
    }

    template<typename T>
    T getCurrentTimeInMilliseconds() noexcept
    {
        static_assert(std::is_arithmetic<T>::value, "Type of the time must be arithmetic.");
        const auto current_time = std::chrono::system_clock::now().time_since_epoch();
        return static_cast<T>(std::chrono::duration_cast<std::chrono::milliseconds>(current_time).count());
    }

}}
