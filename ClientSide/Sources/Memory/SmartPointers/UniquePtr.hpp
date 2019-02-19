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

#include "../INonCopyable.hpp"
#include "../Allocators/PoolAllocator.hpp"

namespace Memory { namespace SmartPointers {

    template<typename Type>
    class UniquePtr : public INonCopyable
    {
    public:
        explicit UniquePtr(Type* pointer, PoolAllocator& allocator)
            : mPointer(pointer), mAllocator(allocator) {}
        explicit UniquePtr(UniquePtr&& another);
        UniquePtr& operator = (UniquePtr&& another);
        Type operator * () const;
        Type* operator -> () const;
        Type* get() const;
        Type* release();
        Type* reset(Type* pointer = nullptr);
        ~UniquePtr();
    private:
        Type* mPointer;
        PoolAllocator& mAllocator;
    };

    template<typename Type>
    UniquePtr<Type>::UniquePtr(UniquePtr&& another)
    {
        mPointer = another.mPointer;
        another.mPointer = nullptr;
        mAllocator = another.mAllocator;
    }

    template<typename Type>
    UniquePtr<Type>& UniquePtr<Type>::operator = (UniquePtr&& another)
    {
        if (mPointer)
            mAllocator.deallocate(mPointer);
        mPointer = another.mPointer;
        another.mPointer = nullptr;
        mAllocator = another.mAllocator;
        return *this;
    }

    template<typename Type>
    Type UniquePtr<Type>::operator * () const
    {
        return *mPointer;
    }

    template<typename Type>
    Type* UniquePtr<Type>::operator -> () const
    {
        return mPointer;
    }

    template<typename Type>
    Type* UniquePtr<Type>::get() const
    {
        return mPointer;
    }

    template<typename Type>
    Type* UniquePtr<Type>::release()
    {
        Type* tmp = mPointer;
        mPointer = nullptr;
        return tmp;
    }

    template<typename Type>
    Type* UniquePtr<Type>::reset(Type* pointer)
    {
        if (mPointer)
            mAllocator.deallocate(mPointer);
        mPointer = pointer;
    }

    template<typename Type>
    UniquePtr<Type>::~UniquePtr()
    {
        if (mPointer)
            mAllocator.deallocate(mPointer);
    }

} }
