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

#include "Memory.hpp"
#include "Allocators/PoolAllocator.hpp"
#include "../Utils/Debug.hpp"

namespace Memory {

    // Singleton
    class StringsMemoryPool 
    {
    public:
        static StringsMemoryPool& getInstance() noexcept;
        void* getMemory() noexcept;
        void returnMemory(void* pointer) noexcept;
        constexpr std::size_t getMemoryBlockSize() const noexcept;
        constexpr std::size_t getCountAllMemoryBlocks() const noexcept;
        constexpr std::size_t getCountFreeMemoryBlocks() const noexcept;
    private:
        static Allocators::PoolAllocator mAllocator;
    };

}
