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
#include "../../Memory/Allocators/LinearAllocator.hpp"

template<typename Type>
class Vector
{
public:
    explicit Vector(std::size_t capacity = 1) noexcept;
    void push(const Type& value) noexcept;
    void pop() noexcept;
    void clear() noexcept;
    Type& getBack() noexcept;
    Type& getFront() noexcept;
    Type& at(std::size_t index) noexcept;
    Type& operator [] (std::size_t index) noexcept;
    Type* getData() noexcept;
    const Type& getBack() const noexcept;
    const Type& getFront() const noexcept;
    const Type& at(std::size_t index) const noexcept;
    const Type& operator [] (std::size_t index) const noexcept;
    bool isEmpty() const noexcept;
    std::size_t getSize() const noexcept;
    ~Vector();
private:
    Type* mArray;
    std::size_t mSize = 0;
    std::size_t mCapacity = 0;
    Memory::Allocators::LinearAllocator mAllocator;
};

template<typename Type>
Vector<Type>::Vector(std::size_t capacity) noexcept
    : mAllocator((capacity * sizeof(Type) < VIRTUAL_PAGE_SIZE) ? 1 : ceil(capacity * sizeof(Type) / VIRTUAL_PAGE_SIZE + 0.5))
{
    mCapacity = mAllocator.getFullMemorySize() / sizeof(Type);
    void* memoryForArray = mAllocator.allocate(mCapacity * sizeof(Type));
    mArray = new (memoryForArray) Type[mCapacity];
}

template<typename Type>
void Vector<Type>::push(const Type& value) noexcept
{
    ASSERT(mSize <= mCapacity, "Vector is full: couldn't add new element");
    mArray[mSize] = value;
    mSize++;
}

template<typename Type>
void Vector<Type>::pop() noexcept
{
    ASSERT(!isEmpty(), "Vector is empty: couldn't destroy last element");
    mArray[mSize] = Type();
    mSize--;
}

template<typename Type>
void Vector<Type>::clear() noexcept
{
    mSize = 0;
    mAllocator.reset();
}

template<typename Type>
Type& Vector<Type>::getBack() noexcept
{
    return mArray[mSize - 1];
}

template<typename Type>
Type& Vector<Type>::getFront() noexcept
{
    return mArray[0];
}

template<typename Type>
Type& Vector<Type>::at(std::size_t index) noexcept
{
    ASSERT(index < mSize, "Vector doesn't contain element with current index");
    return mArray[index];
}

template<typename Type>
Type& Vector<Type>::operator [] (std::size_t index) noexcept
{
    return mArray[index];
}

template<typename Type>
Type* Vector<Type>::getData() noexcept
{
    return mArray;
}

template<typename Type>
const Type& Vector<Type>::getBack() const noexcept
{
    return mArray[mSize - 1];
}

template<typename Type>
const Type& Vector<Type>::getFront() const noexcept
{
    return mArray[0];
}

template<typename Type>
const Type& Vector<Type>::at(std::size_t index) const noexcept
{
    ASSERT(index < mSize, "Vector doesn't contain element with current index");
    return mArray[index];
}

template<typename Type>
const Type& Vector<Type>::operator [] (std::size_t index) const noexcept
{
    return mArray[index];
}

template<typename Type>
bool Vector<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
std::size_t Vector<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
Vector<Type>::~Vector()
{
    clear();
}
