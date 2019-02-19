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

#include "Allocator.hpp"
#include "../../Utils/Debug.hpp"

namespace Memory { namespace Allocators {

    class LinearAllocator : public Allocator<LinearAllocator>
    {
    public:
        explicit LinearAllocator(std::size_t countVirtualPages);
        void* allocate(std::size_t size, std::size_t alignment = 0) noexcept;
        void deallocate(void* pointer) noexcept;
        void reset() noexcept;
        ~LinearAllocator();
    };

} }
