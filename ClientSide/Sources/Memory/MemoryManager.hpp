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

#include "./INonCopyable.hpp"
#include "../Utils/Debug.hpp"
#include "../EventSystem/EventManager.hpp"

#define VIRTUAL_PAGE_SIZE 4096
#define COUNT_ALLOCATED_PAGES 7000

namespace Memory {

    // Singleton
    class MemoryManager : public INonCopyable
    {
    public:
        void* getMemoryPages(std::size_t countVirtualPages = 1) noexcept;
        void showVirtualPagesState() noexcept;
        void showVirtualPageDump(std::size_t index) noexcept;
        std::size_t getVirtualPageIndex(void* pointer) noexcept;
        void returnMemoryPage(void* pointer) noexcept;
        static MemoryManager& getInstance();
    private:
        MemoryManager();
        ~MemoryManager();
        MemoryManager(MemoryManager const&) = delete;
        MemoryManager& operator = (MemoryManager const&) = delete;
    private:
        std::mutex mMutex;
        void* mVirtualPages[COUNT_ALLOCATED_PAGES] = { NULL };
        bool  mUsedPages[COUNT_ALLOCATED_PAGES] = { false };
    };

}
