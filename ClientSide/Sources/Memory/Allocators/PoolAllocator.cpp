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

#include "PoolAllocator.hpp"

Memory::Allocators::PoolAllocator::PoolAllocator(std::size_t countVirtualPages, std::size_t chunkSize)
    : Allocator<PoolAllocator>(countVirtualPages * VIRTUAL_PAGE_SIZE), mChunkSize(chunkSize)
{
    ASSERT(chunkSize != 0, "Empty chunk size for allocation.");
    ASSERT(countVirtualPages != 0, "Empty count of virtual pages for allocation.");
    mBasePointer = MemoryManager::getInstance().getMemoryPages(countVirtualPages);
    ASSERT(mBasePointer, "Memory was not allocated.");
    for (std::size_t i = 0; i < mSize / mChunkSize; i++)
    {
        std::size_t chunkAddress = reinterpret_cast<std::size_t>(mBasePointer) + i * mChunkSize;
        Chunk* newFreeChunk = reinterpret_cast<Chunk*>(chunkAddress);
        newFreeChunk->next = mChunksHead;
        mChunksHead = newFreeChunk;
    }
}

void* Memory::Allocators::PoolAllocator::allocate(std::size_t size) noexcept
{
    ASSERT(mChunkSize == size, "Empty chunk size for allocation.");
    if (mOffset + mChunkSize > mSize)
        return nullptr;

    mOffset += mChunkSize;
    Chunk* freeChunk = mChunksHead;
    mChunksHead = mChunksHead->next;
    return reinterpret_cast<void*>(freeChunk);
}

void Memory::Allocators::PoolAllocator::deallocate(void* pointer) noexcept
{
    if (mOffset == 0)
        return;

    mOffset -= mChunkSize;
    Chunk* newFreeChunk = reinterpret_cast<Chunk*>(pointer);
    newFreeChunk->next = mChunksHead;
    mChunksHead = newFreeChunk;
}

void Memory::Allocators::PoolAllocator::reset() noexcept
{
    mOffset = 0;
    for (std::size_t i = 0; i < mSize / mChunkSize; i++)
    {
        std::size_t chunkAddress = reinterpret_cast<std::size_t>(mBasePointer) + i * mChunkSize;
        Chunk* newFreeChunk = reinterpret_cast<Chunk*>(chunkAddress);
        newFreeChunk->next = mChunksHead;
        mChunksHead = newFreeChunk;
    }
}

Memory::Allocators::PoolAllocator::~PoolAllocator()
{
    std::uint8_t countAllocatedPages = mSize / VIRTUAL_PAGE_SIZE;
    std::size_t baseAddress = reinterpret_cast<std::size_t>(mBasePointer);
    for (std::uint8_t i = 0; i < countAllocatedPages; i++) 
    {
        std::size_t address = baseAddress + (i * VIRTUAL_PAGE_SIZE);
        MemoryManager::getInstance().returnMemoryPage(reinterpret_cast<void*>(address));
    }
}
