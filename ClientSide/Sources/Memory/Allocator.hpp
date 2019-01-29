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

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "IAllocatable.hpp"
#include "INonCopyable.hpp"

namespace Memory {

    // Abstract class
    template<class AllocatorType>
    class Allocator : private INonCopyable
    {
    public:
        explicit Allocator(std::size_t totalSize) 
            : INonCopyable(), mSize(totalSize) {}
        std::size_t getFullMemorySize() const noexcept;
        std::size_t getUsedMemorySize() const noexcept;
        std::size_t getFreeMemorySize() const noexcept;
        IAllocatable* allocate(std::size_t size, std::size_t alignment) noexcept;
        void deallocate(IAllocatable* pointer) noexcept;
        void reset() noexcept;
    protected:
        std::size_t mSize = 0;
        std::size_t mOffset = 0;
        IAllocatable* mpBasePointer = nullptr;
    };

    template<class AllocatorType>
    std::size_t Allocator<AllocatorType>::getFullMemorySize() const noexcept
    {
        return mSize;
    }

    template<class AllocatorType>
    std::size_t Allocator<AllocatorType>::getUsedMemorySize() const noexcept
    {
        return mOffset;
    }

    template<class AllocatorType>
    std::size_t Allocator<AllocatorType>::getFreeMemorySize() const noexcept
    {
        return mSize - mOffset;
    }

    template<class AllocatorType>
    IAllocatable* Allocator<AllocatorType>::allocate(std::size_t size, std::size_t alignment) noexcept
    {
        return static_cast<AllocatorType*>(this)->allocate(size, alignment);
    }

    template<class AllocatorType>
    void Allocator<AllocatorType>::deallocate(IAllocatable* pointer) noexcept
    {
        static_cast<AllocatorType*>(this)->free(pointer);
    }

    template<class AllocatorType>
    void Allocator<AllocatorType>::reset() noexcept
    {
        static_cast<AllocatorType*>(this)->reset();
    }

}
