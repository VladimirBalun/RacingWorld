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

Memory::LinearAllocator::LinearAllocator(std::size_t totalSize) 
    : Allocator<LinearAllocator>(totalSize)
{
    _head_pointer = malloc(totalSize);
    if (!_head_pointer)
        throw std::runtime_error("Memory was not allocated.");
}

void* Memory::LinearAllocator::allocate(std::size_t size, std::size_t alignment) noexcept 
{
    std::size_t padding = 0;
    std::size_t paddedAddress = 0;
    const std::size_t currentAddress = reinterpret_cast<std::size_t>(_head_pointer) + _offset;

    if (alignment != 0 && _offset % alignment != 0) 
        padding = calculate_padding(currentAddress, alignment);
    if (_offset + padding + size > _totalSize) 
        return nullptr;
    
    _offset += padding;
    const std::size_t nextAddress = currentAddress + padding;
    _offset += size;

    _used = _offset;
    _peak = std::max(_peak, _used);

    return reinterpret_cast<void*>(nextAddress);
}

void Memory::LinearAllocator::free(void* pointer) noexcept 
{
    assert(false && "Free() does not work for current type allocator. Use Reset() method");
}

void Memory::LinearAllocator::reset() noexcept 
{
    _offset = _used = _peak = 0;
}

Memory::LinearAllocator::~LinearAllocator()
{
    free(_head_pointer);
    _head_pointer = nullptr;
}
