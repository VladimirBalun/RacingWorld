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

    #include <cstdio>
    #include <cassert>

    #define LOG_DEBUG(text) \
        printf("[DEBUG] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, (text));

    #define LOG_INFO(text) \
        printf("[INFO] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, (text));

    #define LOG_WARNING(text) \
        printf("[WARNING] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, (text));
        
    #define LOG_ERROR(text) \
        printf("[ERROR] [%s] [%s:%d] - %s\n", __TIMESTAMP__, __FILE__, __LINE__, (text));

    #define ASSERT(condition, message) \
        assert(condition && message);

    #define STATIC_ASSERT(condition, message) \
        static_assert(condition, message);

#else // _DEBUG

    #define LOG_DEBUG(text) \
        ( (void)0 )

    #define LOG_INFO(text) \
        ( (void)0 )

    #define LOG_WARNING(text) \
        ( (void)0 )

    #define LOG_ERROR(text) \
        ( (void)0 )

    #define ASSERT(condition, message) \
        ( (void)0 )

    #define STATIC_ASSERT(condition, message) \
        ( (void)0 )

#endif // ! _DEBUG
