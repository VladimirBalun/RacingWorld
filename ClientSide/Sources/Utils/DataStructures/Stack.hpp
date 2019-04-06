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
class Stack : private Memory::INonCopyable
{
    struct Node
    {
        Type data = Type{};
        Node* next = nullptr;
    };
public:
    explicit Stack(std::uint8_t countVirtualPages = 1) noexcept
        : mAllocator(countVirtualPages, sizeof(Node)) {}
    template<typename... Arguments>
    void emplace(Arguments&&... arguments) noexcept;
    void push(const Type& value) noexcept;
    void pop() noexcept;
    void clear() noexcept;
    Type getTop() noexcept;
    constexpr bool isEmpty() const noexcept;
    constexpr std::size_t getSize() const noexcept;
private:
    std::size_t mSize = 0;
    Node *mHead = nullptr;
    Memory::Allocators::PoolAllocator mAllocator;
};

template<typename Type>
template<typename... Arguments>
void Stack<Type>::emplace(Arguments&&... arguments) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ {std::forward<Arguments>(arguments)...} };
    newNode->next = mHead;
    mHead = newNode;
    mSize++;
}

template<typename Type>
void Stack<Type>::push(const Type& value) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ value, mHead };
    mHead = newNode;
    mSize++;
}

template<typename Type>
void Stack<Type>::pop() noexcept
{
    ASSERT(mHead, "Could not erase elememnt: Stack is empty.");
    Node *temp = mHead;
    mHead = mHead->next;
    mAllocator.deallocate(static_cast<void*>(temp));
    mSize--;
}

template<typename Type>
constexpr bool Stack<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
constexpr std::size_t Stack<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
void Stack<Type>::clear() noexcept
{
    Node *iterator = mHead;
    while (iterator)
    {
        Node* temp = iterator;
        iterator = iterator->next;
        mAllocator.deallocate(static_cast<void*>(temp));
    }

    mHead = nullptr;
    mSize = 0;
}

template<typename Type>
Type Stack<Type>::getTop() noexcept
{
    ASSERT(mHead, "Could not get elememnt: Stack is empty.");
    return mHead->data;
}
