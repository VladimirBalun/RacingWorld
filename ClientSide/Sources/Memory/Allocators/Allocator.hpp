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

#include <cstdio>
#include <cstdlib>

#include "../INonCopyable.hpp"
#include "../MemoryManager.hpp"

#define ONE_VIRTUAL_PAGE    1
#define TWO_VIRTUAL_PAGES   2
#define THREE_VIRTUAL_PAGES 3
#define FOUR_VIRTUAL_PAGES  4
#define FIVE_VIRTUAL_PAGES  5
#define SIX_VIRTUAL_PAGES   6
#define SEVEN_VIRTUAL_PAGES 7
#define EIGHT_VIRTUAL_PAGES 8
#define NINE_VIRTUAL_PAGES  9

namespace Memory { namespace Allocators {

    // Abstract class
    template<class AllocatorType>
    class Allocator : private INonCopyable
    {
    public:
        explicit Allocator(std::size_t totalSize) 
            : INonCopyable(), mSize(totalSize) {}
        constexpr std::size_t getFullMemorySize() const noexcept;
        constexpr std::size_t getCountVirtualPages() const noexcept;
        constexpr std::size_t getUsedMemorySize() const noexcept;
        constexpr std::size_t getFreeMemorySize() const noexcept;
        void* getBasePinter() const noexcept;
        void* allocate(std::size_t size) noexcept;
        void deallocate(void* pointer) noexcept;
        void reset() noexcept;
    protected:
        std::size_t mSize = 0;
        std::size_t mOffset = 0;
        void* mBasePointer = nullptr;
    };


    template<class AllocatorType>
    constexpr std::size_t Allocator<AllocatorType>::getFullMemorySize() const noexcept
    {
        return mSize;
    }

    template<class AllocatorType>
    constexpr std::size_t Allocator<AllocatorType>::getCountVirtualPages() const noexcept
    {
        return mSize / VIRTUAL_PAGE_SIZE;
    }

    template<class AllocatorType>
    constexpr std::size_t Allocator<AllocatorType>::getUsedMemorySize() const noexcept
    {
        return mOffset;
    }

    template<class AllocatorType>
    constexpr std::size_t Allocator<AllocatorType>::getFreeMemorySize() const noexcept
    {
        return mSize - mOffset;
    }

    template<class AllocatorType>
    void* Allocator<AllocatorType>::getBasePinter() const noexcept
    {
        return mBasePointer;
    }

    template<class AllocatorType>
    void* Allocator<AllocatorType>::allocate(std::size_t size) noexcept
    {
        return static_cast<AllocatorType*>(this)->allocate(size);
    }

    template<class AllocatorType>
    void Allocator<AllocatorType>::deallocate(void* pointer) noexcept
    {
        static_cast<AllocatorType*>(this)->free(pointer);
    }

    template<class AllocatorType>
    void Allocator<AllocatorType>::reset() noexcept
    {
        static_cast<AllocatorType*>(this)->reset();
    }

 #ifdef _DEBUG

    template<class AllocatorType>
    void showAllocatorMemoryState(const Allocator<AllocatorType>& allocator) 
    {
        printf("\nMemory state of alllocator\n"
            " - Count virtual pages: %zu\n"
            " - Full size of memory: %zu bytes\n"
            " - Used memory: %zu bytes\n"
            " - Free memory: %zu bytes\n\n",
            allocator.getCountVirtualPages(),
            allocator.getFullMemorySize(),
            allocator.getUsedMemorySize(),
            allocator.getFreeMemorySize());
        printf("Memory dump of allocator");
        void* baseAddress = allocator.getBasePinter();
        MemoryManager& memoryManager = MemoryManager::getInstance();
        std::size_t startPageIndex = memoryManager.getVirtualPageIndex(baseAddress);
        for (size_t i = startPageIndex; i < startPageIndex + allocator.getCountVirtualPages(); i++)
            memoryManager.showVirtualPageDump(i);
    }

#else // _DEBUG

    template<class AllocatorType>
    void showAllocatorMemoryState(const Allocator<AllocatorType>& allocator)
    {
    }

#endif // ! _DEBUG

} }
