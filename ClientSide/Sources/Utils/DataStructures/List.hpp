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
class List : public Memory::INonCopyable
{
public:
    explicit List(std::uint8_t countVirtualPages = 1) noexcept
        : mAllocator(countVirtualPages, sizeof(Node)) {}
    template<typename... Arguments>
    void emplaceBack(Arguments&&... arguments) noexcept;
    template<typename... Arguments>
    void emplaceFront(Arguments&&... arguments) noexcept;
    void pushBack(const Type& value) noexcept;
    void pushFront(const Type& value) noexcept;
    void popBack() noexcept;
    void popFront() noexcept;
    void clear() noexcept;
    Type& getBack() noexcept;
    Type& getFront() noexcept;
    const Type& getBack() const noexcept;
    const Type& getFront() const noexcept;
    bool isEmpty() const noexcept;
    std::size_t getSize() const noexcept;
    ~List();
private:
    struct Node
    {
        Type value;
        Node* next = nullptr;
        Node* prev = nullptr;
    };
private:
    void addToEndList(Node* newNode) noexcept;
    void addToBeginList(Node* newNode) noexcept;
private:
    std::size_t mSize = 0;
    Node* mHead = nullptr;
    Node* mTail = nullptr;
    Memory::Allocators::PoolAllocator mAllocator;
};

template<typename Type>
template<typename... Arguments>
void List<Type>::emplaceBack(Arguments&&... arguments) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ {std::forward<Arguments>(arguments)...}};
    addToEndList(newNode);
}

template<typename Type>
template<typename... Arguments>
void List<Type>::emplaceFront(Arguments&&... arguments) noexcept 
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ {std::forward<Arguments>(arguments)...}};
    addToBeginList(newNode);
}

template<typename Type>
void List<Type>::pushBack(const Type& value) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ value };
    addToEndList(newNode);
}

template<typename Type>
void List<Type>::pushFront(const Type& value) noexcept
{
    void* memoryForNode = mAllocator.allocate(sizeof(Node));
    Node* newNode = new (memoryForNode) Node{ value };
    addToBeginList(newNode);
}

template<typename Type>
void List<Type>::addToEndList(Node* newNode) noexcept
{
    if (isEmpty())
    {
        mHead = mTail = newNode;
    }
    else
    {
        mTail->next = newNode;
        newNode->prev = mTail;
        mTail = newNode;
    }
    mSize++;
}

template<typename Type>
void List<Type>::addToBeginList(Node* newNode) noexcept
{
    if (isEmpty())
    {
        mHead = mTail = newNode;
    }
    else
    {
        mHead->prev = newNode;
        newNode->next = mHead;
        mHead = newNode;
    }
    mSize++;
}

template<typename Type>
void List<Type>::popBack() noexcept
{
    ASSERT(mTail, "Could not erase back elememnt: List is empty.");
    Node* temp = mTail;
    mTail = mTail->prev;
    mAllocator.deallocate(static_cast<void*>(temp));
    mSize--;
}

template<typename Type>
void List<Type>::popFront() noexcept
{
    ASSERT(mTail, "Could not erase front elememnt: List is empty.");
    Node* temp = mHead;
    mHead = mHead->next;
    mAllocator.deallocate(static_cast<void*>(temp));
    mSize--;
}

template<typename Type>
void List<Type>::clear() noexcept
{
    mSize = 0;
    Node* iterator = mHead;
    while (iterator) 
    {
        Node* temp = iterator;
        iterator = iterator->next;
        mAllocator.deallocate(static_cast<void*>(temp));
    }
}

template<typename Type>
Type& List<Type>::getBack() noexcept
{
    ASSERT(mTail, "Could not get back elememnt: List is empty.");
    return mTail->value;
}

template<typename Type>
Type& List<Type>::getFront() noexcept 
{
    ASSERT(mTail, "Could not get front elememnt: List is empty.");
    return mHead->value;
}

template<typename Type>
const Type& List<Type>::getBack() const noexcept
{
    ASSERT(mTail, "Could not get back elememnt: List is empty.");
    return mTail->value;
}

template<typename Type>
const Type& List<Type>::getFront() const noexcept
{
    ASSERT(mTail, "Could not get front elememnt: List is empty.");
    return mHead->value;
}

template<typename Type>
bool List<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
std::size_t List<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
List<Type>::~List()
{
    clear();
}
