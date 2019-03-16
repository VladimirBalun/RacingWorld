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

#include "LinearAllocator.hpp"

Memory::Allocators::LinearAllocator::LinearAllocator(size_t countVirtualPages)
    : Allocator<LinearAllocator>(countVirtualPages * VIRTUAL_PAGE_SIZE)
{
    ASSERT(countVirtualPages != 0, "Empty size of memory for allocation.");
    mBasePointer = MemoryManager::getInstance().getMemoryPages(countVirtualPages);
    ASSERT(mBasePointer, "Memory was not allocated.");
}

void* Memory::Allocators::LinearAllocator::allocate(std::size_t size) noexcept
{
    if (mOffset + size > mSize)
    {
        LOG_WARNING("Memory is over in linear allocator");
        showAllocatorMemoryState<LinearAllocator>(*this);
        return nullptr;
    }

    std::size_t allocatedPointer = reinterpret_cast<std::size_t>(mBasePointer) + mOffset;
    mOffset += size;
    return reinterpret_cast<void*>(allocatedPointer);
}

void Memory::Allocators::LinearAllocator::deallocate(void* pointer) noexcept
{
    ASSERT(false, "Current allocator does not support this method. Use reset().");
}

void Memory::Allocators::LinearAllocator::reset() noexcept
{
    mOffset = 0;
}

Memory::Allocators::LinearAllocator::~LinearAllocator()
{
    std::size_t countAllocatedPages = mSize / VIRTUAL_PAGE_SIZE;
    std::size_t baseAddress = reinterpret_cast<std::size_t>(mBasePointer);
    for (std::size_t i = 0; i < countAllocatedPages; i++)
    {
        std::size_t address = baseAddress + (i * VIRTUAL_PAGE_SIZE);
        MemoryManager::getInstance().returnMemoryPage(reinterpret_cast<void*>(address));
    }
}
