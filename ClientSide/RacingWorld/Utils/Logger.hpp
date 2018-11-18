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

#include <iostream>

#ifdef _DEBUG

    #include <thread>

    #define LOG_DEBUG \
        std::cout << "[DEBUG] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " 

    #define LOG_WARNING \
        std::cerr << "[WARNING] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " 

    #define LOG_INFO \
        std::cout << "[INFO] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " 

    #define LOG_ERROR \
        std::cerr << "[ERROR] [" << std::this_thread::get_id() << "] [" << __TIMESTAMP__ << "] [" << __FILE__ << ":" << __LINE__ << "] - " 

#else

    struct NullBuffer : public std::streambuf
    {
        int overflow(int count) { return count; }
    };

    static NullBuffer nullBuffer;
    static std::ostream nullStream(&nullBuffer);

    #define LOG_DEBUG \
        nullStream

    #define LOG_WARNING \
        nullStream

    #define LOG_INFO \
        std::cout << "[INFO] [" << __TIMESTAMP__ << "] - " 

    #define LOG_ERROR \
        std::cerr << "[ERROR] [" << __TIMESTAMP__ << "] - " 

#endif // _DEBUG
