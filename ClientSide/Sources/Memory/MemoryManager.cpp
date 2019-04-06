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

#include <iostream>

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
    std::size_t basePointerAddress = reinterpret_cast<unsigned long long>(*mVirtualPages);
    for (std::size_t i = 0; i < COUNT_ALLOCATED_PAGES; i += 5) 
    {
        mVirtualPages[i] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * i));
        mVirtualPages[i + 1] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * (i + 1)));
        mVirtualPages[i + 2] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * (i + 2)));
        mVirtualPages[i + 3] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * (i + 3)));
        mVirtualPages[i + 4] = reinterpret_cast<void*>(basePointerAddress + (VIRTUAL_PAGE_SIZE * (i + 4)));
        memset(mVirtualPages[i], NULL, VIRTUAL_PAGE_SIZE * 5);
    }
}

void* Memory::MemoryManager::getMemoryPages(std::size_t countVirtualPages) noexcept
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::size_t i = 0; i < COUNT_ALLOCATED_PAGES; i++)
    {
        bool isExistEmptyPlace = true;
        for (std::size_t j = 0; j < countVirtualPages; j++)
        {
            if (mUsedPages[i + j])
            {
                isExistEmptyPlace = false;
                break;
            }
        }
        if (isExistEmptyPlace)
        {
            for (std::size_t j = 0; j < countVirtualPages; j++)
                mUsedPages[i + j] = true;
            return mVirtualPages[i];
        }
    }

    ASSERT(false, "Out of memory. Memory manager doesn't have more pages.");
    return nullptr;
}

void Memory::MemoryManager::showVirtualPagesState() noexcept
{
    printf("..::Vurtual pages dump::..\n");
    printf("Free page: | * |\n");
    printf("Used page: | $ |\n");
    printf("Count virtual pages: %i\n\n", COUNT_ALLOCATED_PAGES);
    for (std::size_t i = 0; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if (!mUsedPages[i])
            printf("#%zu virtual page - %p[ * ]\n", i, mVirtualPages[i]);
        else
            printf("#%zu virtual page - %p[ $ ]\n", i, mVirtualPages[i]);
    }
}

void Memory::MemoryManager::showVirtualPageDump(std::size_t index) noexcept
{
    printf("\n\n..::Vurtual page[%zu] dump::..\n", index);

    std::uint8_t counter = 32;
    std::uint8_t* start = reinterpret_cast<std::uint8_t*>(mVirtualPages[index]);
    std::uint8_t* end = reinterpret_cast<std::uint8_t*>(mVirtualPages[index + 1]);
    for (std::uint8_t* i = start; i < end; i++)
    {
        if (counter == 32)
        {
            counter = 0;
            printf("\n[%p] - ", i);
        }
        
        if (*i == NULL)
            printf("00 ");
        else
            printf("%x ", (*i) & 0xff);
        counter++;
    }

}

std::size_t Memory::MemoryManager::getVirtualPageIndex(void* pointer) noexcept
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::size_t i = 0; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if ((std::size_t) mVirtualPages[i] == (std::size_t) pointer)
            return i;
    }

    return 0;
}

void Memory::MemoryManager::returnMemoryPage(void* pointer) noexcept
{
    std::lock_guard<std::mutex> lock(mMutex);
    for (std::size_t i = 0; i < COUNT_ALLOCATED_PAGES; i++)
    {
        if ((std::size_t) mVirtualPages[i] == (std::size_t) pointer)
        {
            mUsedPages[i] = false;
            memset(mVirtualPages[i], NULL, VIRTUAL_PAGE_SIZE);
            return;
        }
    }

    ASSERT(false, "Incorrect address of memory page.");
}

Memory::MemoryManager::~MemoryManager() 
{
    free(*mVirtualPages);
}
