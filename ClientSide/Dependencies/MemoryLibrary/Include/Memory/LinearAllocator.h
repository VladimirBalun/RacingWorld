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

#include "Utils.hpp"
#include "Allocator.hpp"

namespace Memory {

    // CRTP
    class LinearAllocator : public Allocator<LinearAllocator>
    {
    public:
        LinearAllocator(const LinearAllocator& other) = delete;
        explicit LinearAllocator(std::size_t totalSize);
        void* allocate(std::size_t size, std::size_t alignment) noexcept;
        void free(void* pointer) noexcept;
        void reset() noexcept;
        ~LinearAllocator();
    private:
        std::size_t _offset = 0;
        void* _head_pointer = nullptr;
    };

}
