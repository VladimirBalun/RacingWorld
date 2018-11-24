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

namespace Memory {

    inline std::size_t calculate_padding(std::size_t base_address, std::size_t alignment) noexcept
    {
        const std::size_t multiplier = (base_address / alignment) + 1;
        const std::size_t aligned_address = multiplier * alignment;
        const std::size_t padding = aligned_address - base_address;
        return padding;
    }

    inline std::size_t calculate_padding_with_header(std::size_t base_address, std::size_t alignment, std::size_t header_size) noexcept
    {
        std::size_t padding = calculate_padding(base_address, alignment);
        std::size_t needed_space = header_size;

        if (padding < needed_space) {
            needed_space -= padding;      
            if (needed_space % alignment > 0)
                padding += alignment * (1 + (needed_space / alignment));
            else
                padding += alignment * (needed_space / alignment);
        }

        return padding;
    }

}
