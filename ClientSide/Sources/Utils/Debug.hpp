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

#include <cassert>
#include <iostream>

#ifdef _DEBUG

    #include <thread>

    #define LOG_DEBUG(text) \
        std::cout << "[DEBUG] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " << (text) << std::endl;

    #define LOG_WARNING(text) \
        std::cout << "[WARNING] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " << (text) << std::endl;

    #define LOG_INFO(text) \
        std::cout << "[INFO] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " << (text) << std::endl;

    #define LOG_ERROR(text) \
        std::cout << "[ERROR] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " << (text) << std::endl;

    #define ASSERT(condition, message) \
        assert(condition && message);

    #define STATIC_ASSERT(condition, message) \
        static_assert(condition, message);

#else // _DEBUG

    #define LOG_DEBUG(text) \
        ( (void)0 )

    #define LOG_WARNING(text) \
        ( (void)0 )

    #define LOG_INFO(text) \
        std::cout << "[INFO] [" << __TIMESTAMP__ << "] - " << (text) << std::endl;

    #define LOG_ERROR(text) \
        std::cerr << "[ERROR] [" << __TIMESTAMP__ << "] - " << (text) << std::endl;

    #define ASSERT(condition, message) \
        ( (void)0 )

    #define STATIC_ASSERT(condition, message) \
        ( (void)0 )

#endif // ! _DEBUG
