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

#include "MemoryManager.hpp"

Memory::MemoryManager& Memory::MemoryManager::getInstance()
{
    static MemoryManager instance;
    return instance;
}

Memory::MemoryManager::MemoryManager() 
{
    *mVirtualPages = malloc(VIRTUAL_PAGE_SIZE * COUNT_ALLOCATED_PAGES);
    std::size_t basePointerAddress = reinterpret_cast<std::size_t>(*mVirtualPages);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++) 
        mVirtualPages[i] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * i));
}

void* Memory::MemoryManager::getMemoryPage()
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if (mUsedPages[i] == PAGE_NOT_USED)
        {
            mUsedPages[i] = PAGE_USED;
            return mVirtualPages[i];
        }
    }

    assert(false && "Out of memory. Memory manager doesn't have more pages.");
    return nullptr; // For disable of warning
}

#include <iostream>

void Memory::MemoryManager::returnMemoryPage(void* pointer)
{
    bool isReleasedPage;
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if ((std::size_t) mVirtualPages[i] == (std::size_t) pointer)
        {
            mUsedPages[i] = PAGE_NOT_USED;
            isReleasedPage = true;
        }
    }

    assert(isReleasedPage && "Incorrect addres of memory page.");
}

Memory::MemoryManager::~MemoryManager() 
{
    VirtualFree(*mVirtualPages, 0, MEM_RELEASE);
}
