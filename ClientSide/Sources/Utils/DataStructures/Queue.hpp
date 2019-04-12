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

#include "../../Utils/Debug.hpp"
#include "../../Memory/INonCopyable.hpp"
#include "../../Memory/Allocators/PoolAllocator.hpp"

template<typename Type>
class Queue : private Memory::INonCopyable
{
    struct Node
    {
        Type data = Type{};
        Node* next = nullptr;
    };
public:
    explicit Queue(std::uint8_t countVirtualPages = 1) noexcept
        : mAllocator(countVirtualPages, sizeof(Node)) {}
    template<typename... Arguments>
    void emplace(Arguments&&... arguments) noexcept;
    void push(const Type& value) noexcept;
    void pop() noexcept;
    void clear() noexcept;
    Type getFront() noexcept;
    constexpr bool isEmpty() const noexcept;
    constexpr std::size_t getSize() const noexcept;
private:
    std::size_t mSize = 0;
    Node *mFirst = nullptr;
    Node *mLast = nullptr;
    Memory::Allocators::PoolAllocator mAllocator;
};

template<typename Type>
template<typename... Arguments>
void Queue<Type>::emplace(Arguments&&... arguments) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ {std::forward<Arguments>(arguments)...} };
    newNode->next = nullptr;
    if (isEmpty())
    {
        mFirst = mLast = newNode;
    }
    else
    {
        if (mSize == 1)
            mFirst->next = newNode;
        mLast->next = newNode;
        mLast = newNode;
    }
    mSize++;

} //dont know how this work

template<typename Type>
void Queue<Type>::push(const Type& value) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ value, mFirst };
    newNode->next = nullptr;
    if (isEmpty())
    {
        mFirst = mLast = newNode;
    }
    else
    {
        if (mSize == 1)
            mFirst->next = newNode;
        mLast->next = newNode;
        mLast = newNode;
    }
    mSize++;
}

template<typename Type>
void Queue<Type>::pop() noexcept
{
    ASSERT(mFirst, "Could not erase elememnt: Queue is empty.");
    Node *delElem = mFirst;
    mFirst = mFirst->next;
    mAllocator.deallocate(static_cast<void*>(delElem));
    mSize--;
}

template<typename Type>
constexpr bool Queue<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
constexpr std::size_t Queue<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
void Queue<Type>::clear() noexcept
{
    ASSERT(mFirst, "Could not clear : Queue is empty.");

    while (mFirst) {
        Node *delElem = mFirst;
        mFirst = mFirst->next;
        mAllocator.deallocate(static_cast<void*>(delElem));
    }
    mLast = nullptr;
    mSize = 0;
}

template<typename Type>
Type Queue<Type>::getFront() noexcept
{
    ASSERT(mFirst, "Could not get elememnt: Queue is empty.");
    return mFirst->data;
}
