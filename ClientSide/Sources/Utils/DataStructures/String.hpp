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
#include "../../Memory/StringsMemoryPool.hpp"
#include "../../Memory/Allocators/LinearAllocator.hpp"

class String
{
    class BaseIterator 
    {
    public:
        explicit BaseIterator() noexcept = default;
        explicit BaseIterator(char* pointer) noexcept
            : mPointer(pointer) {}
        BaseIterator& operator = (char* pointer) noexcept;
        BaseIterator& operator ++ () noexcept;
        bool operator != (const BaseIterator& another) const noexcept;
    protected:
        char* mPointer = nullptr;
    };
public:
    class Iterator : public BaseIterator
    {
    public:
        explicit Iterator() noexcept = default;
        explicit Iterator(char* pointer) noexcept
            : BaseIterator(pointer) {}
        char& operator * () noexcept;
    };
    class ConstIterator : public BaseIterator
    {
    public:
        explicit ConstIterator() noexcept = default;
        explicit ConstIterator(char* pointer) noexcept
            : BaseIterator(pointer) {}
        const char& operator * () const noexcept;
    };
public:
    explicit String() noexcept;
    explicit String(const char* string) noexcept;
    explicit String(const char* string, std::size_t length) noexcept;
    explicit String(const String& another) noexcept;
    explicit String(String&& another) noexcept;
    String& operator = (const String& another) noexcept;
    String& operator = (String&& another) noexcept;
    void clear() noexcept;
    void append(const char* string) noexcept;
    void append(const String& string) noexcept;
    String substr(std::size_t position, std::size_t count) noexcept;
    void popBack() noexcept;
    void pushBack(char symbol) noexcept;
    const char* getData() const noexcept;
    char at(std::size_t index) const noexcept;
    char getBack() const noexcept;
    char getFront() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    constexpr std::size_t getLength() const noexcept;
    std::size_t getMaxLenght() const noexcept;
    bool isEmpty() const noexcept;
    bool isEqual(const String& another) const noexcept;
    operator bool() const noexcept;
    char operator [] (std::size_t index) const noexcept;
    bool operator == (const String& another) const noexcept;
    bool operator != (const String& another) const noexcept;
    ~String();
private:
    std::size_t mSize = 0;
    char* mString = nullptr;
};

inline String getParentPath(char* fullPath) noexcept 
{
    const char* lastSlash = strrchr(fullPath, '\\');
    return String(fullPath, static_cast<std::size_t>(lastSlash - fullPath));
}

inline String getPathWithoutFilename(const String& fullPath) noexcept 
{
    const char* lastSlash = strrchr(fullPath.getData(), '\\');
    return String(fullPath.getData(), static_cast<std::size_t>(lastSlash - fullPath.getData() + 1));
}

inline String::String() noexcept
{
    Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
    void* memoryForString = stringsMemoryPool.getMemory();
    mString = static_cast<char*>(memoryForString);
#ifdef _DEBUG
    std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
}

inline String::String(const char* string) noexcept
{
    Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
    void* memoryForString = stringsMemoryPool.getMemory();
    mString = static_cast<char*>(memoryForString);
    const std::size_t stringLength = strlen(string);
    ASSERT(stringLength < stringsMemoryPool.getMemoryBlockSize(),
        "Incorrect size of the string: string is more than memory block for string.");
#ifdef _DEBUG
    std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
    strcpy_s(mString, stringLength + 1, string);
    mSize = stringLength;
}

inline String::String(const char* string, std::size_t length) noexcept
{
    Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
    void* memoryForString = stringsMemoryPool.getMemory();
    mString = static_cast<char*>(memoryForString);
    ASSERT(length < stringsMemoryPool.getMemoryBlockSize(),
        "Incorrect size of the string: string is more than memory block for string.");
#ifdef _DEBUG
    std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
    strncpy_s(mString, strlen(string) + 1, string, length);
    mSize = length;
}

inline String::String(const String& another) noexcept
{
    Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
    void* memoryForString = stringsMemoryPool.getMemory();
    mString = static_cast<char*>(memoryForString);
#ifdef _DEBUG
    std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
    strcpy_s(mString, another.mSize + 1, another.mString);
    mSize = another.mSize;
}

inline String::String(String&& another) noexcept
{
    mSize = another.mSize;
    mString = another.mString;
    another.mSize = 0;
    another.mString = nullptr;
}

inline String& String::operator = (const String& another) noexcept
{
    if (this != &another)
    {
        Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
#ifdef _DEBUG
        if (mString)
        {
            std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
        }
#endif // _DEBUG
        strcpy_s(mString, another.mSize + 1, another.mString);
        mSize = another.mSize;
        stringsMemoryPool.getMemory();
    }
    return *this;
}

inline String& String::operator = (String&& another) noexcept
{
    if (this != &another)
    {
        if (mString)
        {
            Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
#ifdef _DEBUG
            std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
            stringsMemoryPool.returnMemory(static_cast<void*>(mString));
        }
        mSize = another.mSize;
        mString = another.mString;
        another.mSize = 0;
        another.mString = nullptr;
    }
    return *this;
}

inline void String::clear() noexcept
{
    mSize = 0;
#ifdef _DEBUG
    Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
    std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
}

inline void String::append(const char* string) noexcept
{
    const std::size_t stringLength = strlen(string);
    ASSERT(stringLength + mSize < Memory::StringsMemoryPool::getInstance().getMemoryBlockSize(),
        "Could not append string: length of the result string will be more than memory block for string.");
    strcpy_s(mString + mSize, stringLength + 1, string);
    mSize += stringLength;
    mString[mSize] = NULL;
}

inline void String::append(const String& string) noexcept
{
    ASSERT(string.mSize + mSize < Memory::StringsMemoryPool::getInstance().getMemoryBlockSize(),
        "Could not append string: length of the result string will be more than memory block for string.");
    strcpy_s(mString + mSize, string.mSize + 1, string.mString);
    mSize += string.mSize;
    mString[mSize] = NULL;
}

inline String String::substr(std::size_t position, std::size_t count) noexcept
{
    ASSERT(position + count < Memory::StringsMemoryPool::getInstance().getMemoryBlockSize(),
        "Could not sub string: position of the source string is more than memory block for string.");
    return String(mString + position, count);
}

inline void String::popBack() noexcept
{
    ASSERT(!isEmpty(), "Could nor erase last symbol: string is empty.");
    mString[mSize - 1] = NULL;
    mSize--;
}

inline void String::pushBack(char symbol) noexcept
{
    mString[mSize] = symbol;
    mString[mSize + 1] = NULL;
    mSize++;
}

inline const char* String::getData() const noexcept
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
    ASSERT(strlen(mString) > index, "String does not contain symbol with current id");
    return mString[index];
}

inline char String::getBack() const noexcept
{
    ASSERT(!isEmpty(), "String does not contain the last symbol: string is emty.");
    return mString[mSize - 1];
}

inline char String::getFront() const noexcept
{
    ASSERT(!isEmpty(), "String does not contain the first symbol: string is emty.");
    return mString[0];
}

constexpr inline std::size_t String::getLength() const noexcept
{
    return mSize;
}

inline std::size_t String::getMaxLenght() const noexcept
{
    Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
    return stringsMemoryPool.getMemoryBlockSize();
}

inline bool String::isEmpty() const noexcept
{
    return mSize == 0;
}

inline bool String::isEqual(const String& another) const noexcept
{
    return strncmp(mString, another.mString, mSize) == 0;
}

inline bool String::operator == (const String& another) const noexcept
{
    return isEqual(another);
}

inline bool String::operator != (const String& another) const noexcept
{
    return !isEqual(another);
}

inline String::Iterator String::begin() noexcept
{
    return Iterator(mString);
}

inline String::Iterator String::end() noexcept
{
    return Iterator(mString + mSize - 2);
}

inline String::ConstIterator String::begin() const noexcept
{
    return ConstIterator(mString);
}

inline String::ConstIterator String::end() const noexcept
{
    return ConstIterator(mString + mSize - 2);
}

inline String::BaseIterator& String::BaseIterator::operator = (char* pointer) noexcept
{ 
    mPointer = pointer; 
    return *this; 
}

inline String::BaseIterator& String::BaseIterator::operator ++ () noexcept
{ 
    mPointer++; 
    return *this;
}

inline bool String::BaseIterator::operator != (const BaseIterator& another) const noexcept
{
    return mPointer != another.mPointer;
}

inline const char& String::ConstIterator::operator * () const noexcept
{ 
    return *mPointer; 
}

inline char& String::Iterator::operator * () noexcept
{
    return *mPointer;
}

inline String::~String()
{
    if (mString) 
    {
        Memory::StringsMemoryPool& stringsMemoryPool = Memory::StringsMemoryPool::getInstance();
#ifdef _DEBUG
        std::fill(mString, mString + stringsMemoryPool.getMemoryBlockSize(), NULL);
#endif // _DEBUG
        stringsMemoryPool.returnMemory(static_cast<void*>(mString));
    }
}
