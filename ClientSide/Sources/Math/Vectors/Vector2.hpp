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
#include <cstdint>
#include <utility>
#include <iterator>

namespace Math {

    template<class Type>
    class Vector2;

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;

    template<class Type>
    Vector2<Type> operator + (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept;
    template<class Type>
    Vector2<Type> operator - (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept;
    template<class Type>
    Vector2<Type> operator * (const Vector2<Type>& vector, Type scalar) noexcept;
    template<class Type>
    bool operator == (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept;
    template<class Type>
    bool operator != (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept;

    template<class Type>
    class Vector2
    {
    public:
        static const std::uint8_t VECTOR_SIZE = 2;

        Vector2() noexcept = default;
        Vector2(const Vector2& anotherVector) noexcept
            : mX(anotherVector.mX), mY(anotherVector.mY) {}
        Vector2(const Type* array) noexcept
            : mX(array[0]), mY(array[1]) {}
        Vector2(Type x, Type y) noexcept
            : mX(x), mY(y) {}

        Type getX() const noexcept;
        Type getY() const noexcept;
        std::size_t getLength() const noexcept;
        void toArray(Type* array) const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;

        void normalize() noexcept;
        void add(const Vector2& anotherVector) noexcept;
        void sub(const Vector2& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector2& operator = (const Vector2& anotherVector) noexcept;
        Vector2& operator += (const Vector2& anotherVector) noexcept;
        Vector2& operator -= (const Vector2& anotherVector) noexcept;
        Vector2& operator *= (Type scalar) noexcept;
    private:        
        Type mX = 0;
        Type mY = 0;
    };

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
    std::size_t Vector2<Type>::getLength() const noexcept
    {
        return static_cast<std::size_t>(sqrt(mX*mX + mY*mY));
    }

    template<class Type>
    void Vector2<Type>::toArray(Type* array) const noexcept
    {
        array[0] = mX;
        array[1] = mY;
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
            mX /= static_cast<Type>(length);
            mY /= static_cast<Type>(length);
        }
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
        return *this;
    }

    template<class Type>
    Vector2<Type>& Vector2<Type>::operator -= (const Vector2& anotherVector) noexcept
    {
        sub(anotherVector);
        return *this;
    }

    template<class Type>
    Vector2<Type>& Vector2<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Vector2<Type> operator + (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return Vector2<Type>(vector.getX() + anotherVector.getX(), vector.getY() + anotherVector.getY());
    }

    template<class Type>
    Vector2<Type> operator - (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return Vector2<Type>(vector.getX() - anotherVector.getX(), vector.getY() - anotherVector.getY());
    }

    template<class Type>
    Vector2<Type> operator * (const Vector2<Type>& vector, Type scalar) noexcept
    {
        return Vector2<Type>(vector.getX() * scalar, vector.getY() * scalar);
    }

    template<class Type>
    bool operator == (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return ( (vector.getX() == anotherVector.getX()) &&
                 (vector.getY() == anotherVector.getY()) );
    }

    template<class Type>
    bool operator != (const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return !(vector == anotherVector);
    }

}
