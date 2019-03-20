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

#include <cstring>

#include "../Debug.hpp"
#include "../../Memory/INonCopyable.hpp"
#include "../../Memory/Allocators/LinearAllocator.hpp"

class String
{
public:
    explicit String(const char* string, Memory::Allocators::LinearAllocator& allocator) noexcept
        : mString(const_cast<char*>(string)), mAllocator(allocator) {}
    explicit String(const char* string, std::size_t length, Memory::Allocators::LinearAllocator& allocator) noexcept;
    void append(const char* anotherString) noexcept;
    const char* getData() const noexcept;
    operator const char* () const noexcept;
    operator bool () const noexcept;
    char operator [] (std::size_t index) const noexcept;
    char at(std::size_t index) const noexcept;
    std::size_t getLength() const noexcept;
private:
    char* mString;
    Memory::Allocators::LinearAllocator& mAllocator;
};

inline String::String(const char* string, std::size_t length, Memory::Allocators::LinearAllocator& allocator) noexcept
    : mAllocator(allocator)
{
    void* memoryForString = mAllocator.allocate(length + 1);
    mString = static_cast<char*>(memoryForString);
    std::fill(mString, mString + length + 1, 0);
    memcpy((void*) mString, (void*) string, length);
}

inline void String::append(const char* anotherString) noexcept
{
    const std::size_t newStringLength = strlen(mString) + strlen(anotherString) + 1;
    char* newString = reinterpret_cast<char*>(mAllocator.allocate(newStringLength));
    std::fill(newString, newString + newStringLength, 0);
    strcat_s(newString, strlen(mString) + 1, mString);
    strcat_s(newString, newStringLength, anotherString);
    mString = newString;
}

inline const char* String::getData() const noexcept
{
    return mString;
}

inline String::operator const char* () const noexcept
{
    return mString;
}

inline String::operator bool() const noexcept
{
    return mString != nullptr;
}

inline char String::operator [] (std::size_t index) const noexcept
{
    return mString[index];
}

inline char String::at(std::size_t index) const noexcept
{
    ASSERT(strlen(mString) > index ,"String does not contain symbol with current id")
    return mString[index];
}

inline std::size_t String::getLength() const noexcept
{
    return strlen(mString);
}
