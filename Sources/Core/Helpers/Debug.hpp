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

#ifdef _DEBUG

    #include <string>

    #define LOG_DEBUG(__text__) \
        printf("[DEBUG] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str())

    #define LOG_INFO(__text__) \
        printf("[INFO] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str())

    #define LOG_WARNING(__text__) \
        printf("[WARNING] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str())
        
    #define LOG_ERROR(__text__) \
        printf("[ERROR] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str())

    #define LOG_PROFILING(__text__) \
        printf("[PROFILING] [%s] - %s\n", __TIMESTAMP__, std::string(__text__).c_str())

    #define LOG_DEBUG_IF(__condition__, __text__) \
        do { \
            if ((__condition__)) \
                printf("[DEBUG] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str()); \
        } while(0, 0) 

    #define LOG_INFO_IF(__condition__, __text__) \
        do { \
            if ((__condition__)) \
                printf("[INFO] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str()); \
        } while(0, 0) 

    #define LOG_WARNING_IF(__condition__, __text__) \
        do { \
            if ((__condition__)) \
                printf("[WARNING] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str()); \
        } while(0, 0) 

    #define LOG_ERROR_IF(__condition__, __text__) \
        do { \
            if ((__condition__)) \
                printf("[ERROR] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, std::string(__text__).c_str()); \
        } while(0, 0) 

    #define ASSERT(__condition__, __message__) \
        assert((__condition__) && std::string(__message__).c_str())

    #define STATIC_ASSERT(__condition__, __message__) \
        static_assert((__condition__), std::string(__message__).c_str())

#else // _DEBUG

    #define LOG_DEBUG(__text__) \
        ( (void)0 )

    #define LOG_INFO(__text__) \
        ( (void)0 )

    #define LOG_WARNING(__text__) \
        ( (void)0 )

    #define LOG_ERROR(__text__) \
        ( (void)0 )

    #define LOG_PROFILING(__text__) \
        ( (void)0 )

    #define LOG_DEBUG_IF(__condition__, __text__) \
        ( (void)0 )

    #define LOG_INFO_IF(__condition__, __text__) \
        ( (void)0 )

    #define LOG_WARNING_IF(__condition__, __text__) \
        ( (void)0 )

    #define LOG_ERROR_IF(__condition__, __text__) \
        ( (void)0 )

    #define ASSERT(__condition__, __message__) \
        ( (void)0 )

    #define STATIC_ASSERT(__condition__, __message__) \
        ( (void)0 )

#endif // ! _DEBUG
