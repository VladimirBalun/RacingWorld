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
    class Vector4
    {
    public:
        static const std::uint8_t VECTOR_SIZE = 4;

        Vector4() noexcept = default;
        Vector4(const Vector4& anotherVector) noexcept;
        Vector4(const Type* array) noexcept;
        Vector4(Type x, Type y, Type z) noexcept
            : mX(x), mY(y), mZ(z), mW(1) {}
        Vector4(Type x, Type y, Type z, Type w) noexcept
            : mX(x), mY(y), mZ(z), mW(w) {}

        Type getX() const noexcept;
        Type getY() const noexcept;
        Type getZ() const noexcept;
        Type getW() const noexcept;
        std::size_t getLength() const noexcept;
        void toArray(Type* array) const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;
        void setZ(Type z) noexcept;
        void setW(Type w) noexcept;

        void normalize() noexcept;
        void add(const Vector4& anotherVector) noexcept;
        void sub(const Vector4& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector4& operator = (const Vector4& anotherVector) noexcept;
        Vector4& operator += (const Vector4& anotherVector) noexcept;
        Vector4& operator -= (const Vector4& anotherVector) noexcept;
        Vector4& operator *= (Type scalar) noexcept;
    private:
        Type mX = 0;
        Type mY = 0;
        Type mZ = 0;
        Type mW = 0;
    };

    template<class Type>
    Vector4<Type> operator + (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;
    template<class Type>
    Vector4<Type> operator - (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;
    template<class Type>
    Vector4<Type> operator * (const Vector4<Type>& vector, Type scalar) noexcept;
    template<class Type>
    bool operator == (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;
    template<class Type>
    bool operator != (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int>;

    template<class Type>
    Vector4<Type>::Vector4(const Vector4& anotherVector) noexcept
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
        mZ = anotherVector.mZ;
        mW = anotherVector.mW;
    }

    template<class Type>
    Vector4<Type>::Vector4(const Type* array) noexcept
    {
        mX = array[0];
        mY = array[1];
        mZ = array[2];
        mW = array[3];
    }

    template<class Type>
    Type Vector4<Type>::getX() const noexcept
    {
        return mX;
    }

    template<class Type>
    Type Vector4<Type>::getY() const noexcept
    {
        return mY;
    }

    template<class Type>
    Type Vector4<Type>::getZ() const noexcept
    {
        return mZ;
    }

    template<class Type>
    Type Vector4<Type>::getW() const noexcept
    {
        return mW;
    }

    template<class Type>
    std::size_t Vector4<Type>::getLength() const noexcept
    {
        return static_cast<std::size_t>(sqrt(mX*mX + mY*mY + mZ*mZ));
    }

    template<class Type>
    void Vector4<Type>::toArray(Type* array) const noexcept
    {
        array[0] = mX;
        array[1] = mY;
        array[2] = mZ;
        array[3] = mW;
    }

    template<class Type>
    void Vector4<Type>::setX(Type x) noexcept
    {
        mX = x;
    }

    template<class Type>
    void Vector4<Type>::setY(Type y) noexcept
    {
        mY = y;
    }

    template<class Type>
    void Vector4<Type>::setZ(Type z) noexcept
    {
        mZ = z;
    }

    template<class Type>
    void Vector4<Type>::setW(Type w) noexcept
    {
        mW = w;
    }

    template<class Type>
    void Vector4<Type>::normalize() noexcept
    {
        const std::size_t length = getLength();
        if (length != 0)
        {
            mX /= static_cast<Type>(length);
            mY /= static_cast<Type>(length);
            mZ /= static_cast<Type>(length);
        }
    }

    template<class Type>
    void Vector4<Type>::add(const Vector4& anotherVector) noexcept
    {
        mX += anotherVector.mX;
        mY += anotherVector.mY;
        mZ += anotherVector.mZ;
    }

    template<class Type>
    void Vector4<Type>::sub(const Vector4& anotherVector) noexcept
    {
        mX -= anotherVector.mX;
        mY -= anotherVector.mY;
        mZ -= anotherVector.mZ;
    }

    template<class Type>
    void Vector4<Type>::mul(Type scalar) noexcept
    {
        mX *= scalar;
        mY *= scalar;
        mZ *= scalar;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator = (const Vector4& anotherVector) noexcept
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
        mZ = anotherVector.mZ;
        mW = anotherVector.mW;
        return *this;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator += (const Vector4& anotherVector) noexcept
    {
        add(anotherVector);
        return *this;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator -= (const Vector4& anotherVector) noexcept
    {
        sub(anotherVector);
        return *this;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Vector4<Type> operator + (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return Vector4<Type>(vector.getX() + anotherVector.getX(), vector.getY() + anotherVector.getY(), vector.getZ() + anotherVector.getZ());
    }

    template<class Type>
    Vector4<Type> operator - (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return Vector4<Type>(vector.getX() - anotherVector.getX(), vector.getY() - anotherVector.getY(), vector.getZ() - anotherVector.getZ());
    }

    template<class Type>
    Vector4<Type> operator * (const Vector4<Type>& vector, Type scalar) noexcept
    {
        return Vector4<Type>(vector.getX() * scalar, vector.getY() * scalar, vector.getZ() * scalar);
    }

    template<class Type>
    bool operator == (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return ( (vector.getX() == anotherVector.getX()) &&
                 (vector.getY() == anotherVector.getY()) &&
                 (vector.getZ() == anotherVector.getZ()) &&
                 (vector.getW() == anotherVector.getW()) );
    }

    template<class Type>
    bool operator != (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return !(vector == anotherVector);
    }

} 
