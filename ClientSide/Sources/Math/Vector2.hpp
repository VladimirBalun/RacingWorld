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

#include <cmath>
#include <array>

namespace Math {

    template<class Type>
    class Vector2
    {
    public:
        Vector2() = default;
        Vector2(const Vector2& anotherVector);
        Vector2(Type x, Type y)
            : mX(x), mY(y) {}

        Type getX() const noexcept;
        Type getY() const noexcept;
        std::array<Type, 2> toArray() const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;

        void normalize() noexcept;
        std::size_t getLength() const noexcept;
        Type dot(const Vector2& anotherVector) noexcept;
        void add(const Vector2& anotherVector) noexcept;
        void sub(const Vector2& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector2& operator = (const Vector2& anotherVector) noexcept;
        Vector2& operator += (const Vector2& anotherVector) noexcept;
        Vector2& operator -= (const Vector2& anotherVector) noexcept;
        Vector2& operator *= (Type scalar) noexcept;

        friend Vector2 operator + (const Vector2& vector, const Vector2& anotherVector) noexcept;
        friend Vector2 operator - (const Vector2& vector, const Vector2& anotherVector) noexcept;
        friend Vector2 operator * (const Vector2& vector, Type scalar) noexcept;
        friend bool operator == (const Vector2& vector, const Vector2& anotherVector) noexcept;
        friend bool operator != (const Vector2& vector, const Vector2& anotherVector) noexcept;
    private:        
        Type mX = 0;
        Type mY = 0;
    };

    template<class Type>
    Vector2<Type>::Vector2(const Vector2& anotherVector)
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
    }

    template<class Type>
    Type Vector2<Type>::getX() const noexcept
    {
        return mX;
    }

    template<class Type>
    Type Vector2<Type>::getY() const noexcept
    {
        return mY;
    }

    template<class Type>
    std::array<Type, 2> Vector2<Type>::toArray() const noexcept
    {
        return std::array<Type, 2> { mX, mY };
    }

    template<class Type>
    void Vector2<Type>::setX(Type x) noexcept
    {
        mX = x;
    }

    template<class Type>
    void Vector2<Type>::setY(Type y) noexcept
    {
        mY = y;
    }

    template<class Type>
    void Vector2<Type>::normalize() noexcept
    {
        const std::size_t length = getLength();
        if (length != 0)
        {
            mX /= length;
            mY /= length;
        }
    }

    template<class Type>
    std::size_t Vector2<Type>::getLength() const noexcept
    {
        return sqrt(mX*mX + mY*mY);
    }

    template<class Type>
    Type Vector2<Type>::dot(const Vector2& anotherVector) noexcept
    {
        return mX*anotherVector.mX + mY*anotherVector.mY;
    }

    template<class Type>
    void Vector2<Type>::add(const Vector2& anotherVector) noexcept
    {
        mX += anotherVector.mX;
        mY += anotherVector.mY;
    }

    template<class Type>
    void Vector2<Type>::sub(const Vector2& anotherVector) noexcept
    {
        mX -= anotherVector.mX;
        mY -= anotherVector.mY;
    }

    template<class Type>
    void Vector2<Type>::mul(Type scalar) noexcept
    {
        mX *= scalar;
        mY *= scalar;
    }

    template<class Type>
    Vector2<Type>& Vector2<Type>::operator = (const Vector2& anotherVector) noexcept
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
        return *this;
    }

    template<class Type>
    Vector2<Type>& Vector2<Type>::operator += (const Vector2& anotherVector) noexcept
    {
        add(anotherVector);
    }

    template<class Type>
    Vector2<Type>& Vector2<Type>::operator -= (const Vector2& anotherVector) noexcept
    {
        sub(anotherVector);
    }

    template<class Type>
    Vector2<Type>& Vector2<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
    }

    template<class Type>
    Vector2<Type> operator + (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return Vector2<Type>(vector.mX + anotherVector.mX, vector.mY + anotherVector.mY);
    }

    template<class Type>
    Vector2<Type> operator - (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return Vector2<Type>(vector.mX - anotherVector.mX, vector.mY - anotherVector.mY);
    }

    template<class Type>
    Vector2<Type> operator * (const Vector2<Type>& vector, Type scalar) noexcept
    {
        return Vector2<Type>(vector.mX * scalar, vector.mY * scalar);
    }

    template<class Type>
    bool operator == (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return ( (vector.mX == anotherVector.mX) &&
                 (vector.mY == anotherVector.mY) );
    }

    template<class Type>
    bool operator != (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return ( (vector.mX != anotherVector.mX) ||
                 (vector.mY != anotherVector.mY) );
    }

}
