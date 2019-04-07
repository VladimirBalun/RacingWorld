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

#include "StringsMemoryPool.hpp"

#define BLOCK_SIZE BYTES_512_SIZE

Memory::Allocators::PoolAllocator Memory::StringsMemoryPool::mAllocator{ KILLOBYTES_512_SIZE / VIRTUAL_PAGE_SIZE,  BLOCK_SIZE };

Memory::StringsMemoryPool& Memory::StringsMemoryPool::getInstance() noexcept
{
    static StringsMemoryPool stringsMemoryPool;
    return stringsMemoryPool;
}

void* Memory::StringsMemoryPool::getMemory() noexcept
{
    ASSERT((mAllocator.getFullMemorySize() - mAllocator.getFreeMemorySize()) > BLOCK_SIZE,
        "Not enought memory in the poll allocator for string allocation.");
    void* pointer = mAllocator.allocate(BLOCK_SIZE);
    ASSERT(pointer, "Memory for string was not allocated.");
    return pointer;
}

void Memory::StringsMemoryPool::returnMemory(void* pointer) noexcept
{
#ifdef _DEBUG
    std::size_t allocatorFreeSize = mAllocator.getFreeMemorySize();
#endif // _DEBUG
    mAllocator.deallocate(pointer);
#ifdef _DEBUG
    ASSERT(allocatorFreeSize < mAllocator.getFreeMemorySize(), 
        "Memory of the string was not deallocated.");
#endif // _DEBUG
}

constexpr std::size_t Memory::StringsMemoryPool::getMemoryBlockSize() const noexcept
{
    return BLOCK_SIZE;
}

constexpr std::size_t Memory::StringsMemoryPool::getCountAllMemoryBlocks() const noexcept
{
    return mAllocator.getFullMemorySize() / BLOCK_SIZE;
}

constexpr std::size_t Memory::StringsMemoryPool::getCountFreeMemoryBlocks() const noexcept
{
    return (mAllocator.getFullMemorySize() - mAllocator.getFreeMemorySize()) / BLOCK_SIZE;
}
