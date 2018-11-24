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

namespace Memory {

    // CRTP
    template <class Type>
    class Allocator
    {
    public:
        Allocator(const Allocator& other) = delete;
        explicit Allocator(std::size_t totalSize) : _totalSize(totalSize) {}
        void* allocate(std::size_t size, std::size_t alignment) noexcept;
        void free(void* pointer) noexcept;
        void reset() noexcept;
    protected:
        std::size_t _used = 0;
        std::size_t _peak = 0;
        std::size_t _totalSize = 0;
    };

    template <class Type>
    void* Allocator<Type>::allocate(std::size_t size, std::size_t alignment) noexcept
    {
        return static_cast<Type*>(this)->allocateImpl(size, alignment);
    }

    template <class Type>
    void Allocator<Type>::free(void* pointer) noexcept
    {
        static_cast<Type*>(this)->freeImpl(pointer);
    }

    template <class Type>
    void Allocator<Type>::reset() noexcept
    {
        static_cast<Type*>(this)->resetImpl();
    }

}
