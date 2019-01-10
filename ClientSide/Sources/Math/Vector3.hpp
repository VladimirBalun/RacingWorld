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
    class Vector3
    {
    public:
        Vector3() = default;
        Vector3(const Vector3& anotherVector);
        Vector3(Type x, Type y, Type z)
            : mX(x), mY(y), mZ(z) {}

        Type getX() const noexcept;
        Type getY() const noexcept;
        Type getZ() const noexcept;
        std::array<Type, 3> toArray() const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;
        void setZ(Type z) noexcept;

        void normalize() noexcept;
        std::size_t getLength() const noexcept;
        Type dot(const Vector3& anotherVector) noexcept;
        void cross(const Vector3& anotherVector) noexcept;
        void add(const Vector3& anotherVector) noexcept;
        void sub(const Vector3& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector3& operator = (const Vector3& anotherVector) noexcept;
        Vector3& operator += (const Vector3& anotherVector) noexcept;
        Vector3& operator -= (const Vector3& anotherVector) noexcept;
        Vector3& operator *= (Type scalar) noexcept;

        friend Vector3 operator + (const Vector3& vector, const Vector3& anotherVector) noexcept;
        friend Vector3 operator - (const Vector3& vector, const Vector3& anotherVector) noexcept;
        friend Vector3 operator * (const Vector3& vector, Type scalar) noexcept;
        friend bool operator == (const Vector3& vector, const Vector3& anotherVector) noexcept;
        friend bool operator != (const Vector3& vector, const Vector3& anotherVector) noexcept;
    private:
        Type mX = 0;
        Type mY = 0;
        Type mZ = 0;
    };

    template<class Type>
    Vector3<Type>::Vector3(const Vector3& anotherVector)
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
        mZ = anotherVector.mZ;
    }

    template<class Type>
    Type Vector3<Type>::getX() const noexcept
    {
        return mX;
    }

    template<class Type>
    Type Vector3<Type>::getY() const noexcept
    {
        return mY;
    }

    template<class Type>
    Type Vector3<Type>::getZ() const noexcept
    {
        return mZ;
    }

    template<class Type>
    std::array<Type, 3> Vector3<Type>::toArray() const noexcept
    {
        return std::array<Type, 3> { mX, mY, mZ };
    }

    template<class Type>
    void Vector3<Type>::setX(Type x) noexcept
    {
        mX = x;
    }

    template<class Type>
    void Vector3<Type>::setY(Type y) noexcept
    {
        mY = y;
    }

    template<class Type>
    void Vector3<Type>::setZ(Type z) noexcept
    {
        mZ = z;
    }

    template<class Type>
    void Vector3<Type>::normalize() noexcept
    {
        const std::size_t length = getLength();
        if (length != 0)
        {
            mX /= length;
            mY /= length;
            mZ /= length;
        }
    }

    template<class Type>
    std::size_t Vector3<Type>::getLength() const noexcept
    {
        return sqrt(mX*mX + mY*mY + mZ*mZ);
    }

    template<class Type>
    Type Vector3<Type>::dot(const Vector3& anotherVector) noexcept
    {
        return mX*anotherVector.mX + mY*anotherVector.mY + mZ*anotherVector.mZ;
    }

    template<class Type>
    void Vector3<Type>::cross(const Vector3& anotherVector) noexcept 
    {
        const Type x = mY*another.mZ - mZ*another.mY;
        const Type y = -(mX*another.mZ - mZ*another.mX);
        const Type z = mX*another.mY - mY*another.mX;
        mX = x;
        mY = y;
        mZ = z;
    }

    template<class Type>
    void Vector3<Type>::add(const Vector3& anotherVector) noexcept
    {
        mX += anotherVector.mX;
        mY += anotherVector.mY;
        mZ += anotherVector.mZ;
    }

    template<class Type>
    void Vector3<Type>::sub(const Vector3& anotherVector) noexcept
    {
        mX -= anotherVector.mX;
        mY -= anotherVector.mY;
        mZ -= anotherVector.mZ;
    }

    template<class Type>
    void Vector3<Type>::mul(Type scalar) noexcept
    {
        mX *= scalar;
        mY *= scalar;
        mZ *= scalar;
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator = (const Vector3& anotherVector) noexcept
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
        mZ = anotherVector.mZ;
        return *this;
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator += (const Vector3& anotherVector) noexcept
    {
        add(anotherVector);
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator -= (const Vector3& anotherVector) noexcept
    {
        sub(anotherVector);
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
    }

    template<class Type>
    Vector3<Type> operator + (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return Vector3<Type>(vector.mX + anotherVector.mX, vector.mY + anotherVector.mY, vector.mZ + anotherVector.mZ);
    }

    template<class Type>
    Vector3<Type> operator - (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return Vector3<Type>(vector.mX - anotherVector.mX, vector.mY - anotherVector.mY, vector.mZ - anotherVector.mZ);
    }

    template<class Type>
    Vector3<Type> operator * (const Vector3<Type>& vector, Type scalar) noexcept
    {
        return Vector3<Type>(vector.mX * scalar, vector.mY * scalar, vector.mZ * scalar);
    }

    template<class Type>
    bool operator == (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return ( (vector.mX == anotherVector.mX) &&
                 (vector.mY == anotherVector.mY) &&
                 (vector.mZ == anotherVector.mZ) );
    }

    template<class Type>
    bool operator != (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return ( (vector.mX != anotherVector.mX) ||
                 (vector.mY != anotherVector.mY) ||
                 (vector.mZ != anotherVector.mZ) );
    }

} 
