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

#include <mutex>
#include <cassert>
#include <Windows.h>

#include "INonCopyable.hpp"
#include "IAllocatable.hpp"

#define VIRTUAL_PAGE_SIZE 4096
#define COUNT_ALLOCATED_PAGES 25

namespace Memory {

    // Singleton
    class MemoryManager : public INonCopyable
    {
    public:
        void* getMemoryPage();
        void returnMemoryPage(void* pointer);
        static MemoryManager& getInstance();
    private:
        MemoryManager();
        ~MemoryManager();
    private:
        static const std::uint8_t PAGE_USED = 1;
        static const std::uint8_t PAGE_NOT_USED = 0;
    private:
        std::mutex mMutex;
        void* mVirtualPages[COUNT_ALLOCATED_PAGES] = { NULL };
        std::uint8_t mUsedPages[COUNT_ALLOCATED_PAGES] = { PAGE_NOT_USED };
    };

}
