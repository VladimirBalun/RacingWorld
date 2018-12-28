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

Memory::LinearAllocator::LinearAllocator(size_t memorySize) 
    : Memory::Allocator<LinearAllocator>(memorySize)
{
    if (memorySize == 0)
        throw std::runtime_error("Incorrect size of memory for allocation.");

    mpBasePointer = (Memory::IAllocatable*) malloc(memorySize);
    if (!mpBasePointer)
        throw std::runtime_error("Memory was not allocated.");
}

Memory::IAllocatable* Memory::LinearAllocator::allocate(std::size_t size, std::size_t alignment) noexcept
{
    std::size_t allocatedPointer = reinterpret_cast<std::size_t>(mpBasePointer) + mOffset;
    mOffset += alignment;
    return reinterpret_cast<IAllocatable*>(allocatedPointer);
}

void Memory::LinearAllocator::free(IAllocatable* pointer) noexcept 
{
    assert(false && "Current allocator does not support this method. Use reset().");
}

void Memory::LinearAllocator::reset() noexcept 
{
    mSize = mOffset = 0;
}

Memory::LinearAllocator::~LinearAllocator() 
{
    ::free(static_cast<void*>(mpBasePointer));
}
