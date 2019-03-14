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
    if (!*mVirtualPages)
        EventSystem::EventManager::getInstance().notifyGlobalError("Memory was not allocated for application");
    std::size_t basePointerAddress = reinterpret_cast<std::size_t>(*mVirtualPages);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++) 
        mVirtualPages[i] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * i));
}

void* Memory::MemoryManager::getMemoryPage() noexcept
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if (!mUsedPages[i])
        {
            mUsedPages[i] = true;
            return mVirtualPages[i];
        }
    }

    ASSERT(false, "Out of memory. Memory manager doesn't have more pages.");
    return nullptr;
}

void Memory::MemoryManager::showVirtualPagesDump() noexcept
{
    printf("..::Vurtual pages dump::..\n");
    printf("Free page: |   |\n");
    printf("Used page: | # |\n");
    printf("Count virtual pages: %i\n\n|", COUNT_ALLOCATED_PAGES);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if (!mUsedPages[i])
            printf("   |");
        else
            printf(" # |");
    }
    printf("\n\n");
}

void Memory::MemoryManager::returnMemoryPage(void* pointer) noexcept
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::uint8_t i = 1; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if ((std::size_t) mVirtualPages[i] == (std::size_t) pointer)
        {
            mUsedPages[i] = false;
            return;
        }
    }

    ASSERT(false, "Incorrect address of memory page.");
}

Memory::MemoryManager::~MemoryManager() 
{
    free(*mVirtualPages);
}
