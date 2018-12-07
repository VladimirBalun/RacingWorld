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

#include "PoolAllocator.h"

Memory::PoolAllocator::PoolAllocator(std::size_t totalSize, std::size_t blockSize)
    : Allocator<PoolAllocator>(totalSize), _blockSize(blockSize)
{
    assert(_totalSize >= 8 && "Block size must be greater or equal to 8");
    assert(_totalSize % _blockSize == 0 && "Total size must be a multiple of block size");
    _head_pointer = malloc(_totalSize);
    if (!_head_pointer)
        throw std::runtime_error("Memory was not allocated.");
}

void* Memory::PoolAllocator::allocate(std::size_t size, std::size_t alignment) noexcept
{
    assert(size == _blockSize && "Allocation size must be equal to block size");
    Node *freePosition = _stack.pop();
    assert(freePosition != nullptr && "The pool allocator is full");

    _used += _blockSize;
    _peak = std::max(_peak, _used);
    return static_cast<void*>(freePosition);
}

void Memory::PoolAllocator::free(void* pointer) noexcept
{
    _used -= _blockSize;
    _stack.push(static_cast<Node*>(pointer));
}

void Memory::PoolAllocator::reset() noexcept
{
    _used = _peak = 0;
    const std::size_t countBlocks = _totalSize / _blockSize;
    for (std::size_t i = 0; i < countBlocks; i++) 
    {
        std::size_t address = reinterpret_cast<std::size_t>(_head_pointer) + i * _blockSize;
        _stack.push(reinterpret_cast<Node*>(address));
    }
}

Memory::PoolAllocator::~PoolAllocator()
{
    free(_head_pointer);
    _head_pointer = nullptr;
}
