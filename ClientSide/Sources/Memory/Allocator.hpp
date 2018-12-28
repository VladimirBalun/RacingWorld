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
        IAllocatable* allocate(std::size_t size, std::size_t alignment) noexcept;
        void free(IAllocatable* pointer) noexcept;
        void reset() noexcept;
    protected:
        std::size_t mSize = 0;
        std::size_t mOffset = 0;
        IAllocatable* mpBasePointer = nullptr;
    };

}
