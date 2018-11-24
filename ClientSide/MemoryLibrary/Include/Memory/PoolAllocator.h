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

#include "Stack.hpp"
#include "Allocator.hpp"

namespace Memory {

    // CRTP
    class PoolAllocator : public Allocator<PoolAllocator> 
    {
        struct FreeHeader {};
        typedef Stack<FreeHeader>::Node Node;
    public:
        PoolAllocator(const PoolAllocator& other) = delete;
        explicit PoolAllocator(std::size_t totalSize, std::size_t blockSize);
        void* allocate(std::size_t size, std::size_t alignment) noexcept;
        void free(void* pointer) noexcept;
        void reset() noexcept;
        ~PoolAllocator();
    private:
        std::size_t _blockSize = 0;
        void* _head_pointer = nullptr;
        Stack<FreeHeader> _stack;
    };

}
