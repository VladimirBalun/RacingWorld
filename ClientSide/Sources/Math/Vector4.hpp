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
    class Vector4
    {
    public:
        static const std::uint8_t VECTOR_SIZE = 4;

        Vector4() = default;
        Vector4(const Vector4& anotherVector);
        Vector4(const Type* array);
        Vector4(Type x, Type y, Type z, Type w)
            : mX(x), mY(y), mZ(z), mW(w) {}

        Type getX() const noexcept;
        Type getY() const noexcept;
        Type getZ() const noexcept;
        Type getW() const noexcept;
        std::size_t getLength() const noexcept;
        void toArray(Type* array) const;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;
        void setZ(Type z) noexcept;
        void setW(Type w) noexcept;

        void normalize() noexcept;
        Type dot(const Vector4& anotherVector) noexcept;
        void cross(const Vector4& anotherVector) noexcept;
        void add(const Vector4& anotherVector) noexcept;
        void sub(const Vector4& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector4& operator = (const Vector4& anotherVector) noexcept;
        Vector4& operator += (const Vector4& anotherVector) noexcept;
        Vector4& operator -= (const Vector4& anotherVector) noexcept;
        Vector4& operator *= (Type scalar) noexcept;

        friend Vector4 operator + (const Vector4& vector, const Vector4& anotherVector) noexcept;
        friend Vector4 operator - (const Vector4& vector, const Vector4& anotherVector) noexcept;
        friend Vector4 operator * (const Vector4& vector, Type scalar) noexcept;
        friend bool operator == (const Vector4& vector, const Vector4& anotherVector) noexcept;
        friend bool operator != (const Vector4& vector, const Vector4& anotherVector) noexcept;
    private:
        Type mX = 0;
        Type mY = 0;
        Type mZ = 0;
        Type mW = 0;
    };

    template<class Type>
    Vector4<Type>::Vector4(const Vector4& anotherVector)
    {
        mX = anotherVector.mX;
        mY = anotherVector.mY;
        mZ = anotherVector.mZ;
        mW = anotherVector.mW;
    }

    template<class Type>
    Vector4<Type>::Vector4(const Type* array)
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
        return sqrt(mX*mX + mY*mY + mZ*mZ);
    }

    template<class Type>
    void Vector4<Type>::toArray(Type* array) const
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
            mX /= length;
            mY /= length;
            mZ /= length;
        }
    }

    template<class Type>
    Type Vector4<Type>::dot(const Vector4& anotherVector) noexcept
    {
        return mX*anotherVector.mX + mY*anotherVector.mY + mZ*anotherVector.mZ;
    }

    template<class Type>
    void Vector4<Type>::cross(const Vector4& anotherVector) noexcept
    {
        const Type x = mY * another.mZ - mZ * another.mY;
        const Type y = -(mX*another.mZ - mZ * another.mX);
        const Type z = mX * another.mY - mY * another.mX;
        mX = x;
        mY = y;
        mZ = z;
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
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator -= (const Vector4& anotherVector) noexcept
    {
        sub(anotherVector);
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
    }

    template<class Type>
    Vector4<Type> operator + (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return Vector4<Type>(vector.mX + anotherVector.mX, vector.mY + anotherVector.mY, vector.mZ + anotherVector.mZ);
    }

    template<class Type>
    Vector4<Type> operator - (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return Vector4<Type>(vector.mX - anotherVector.mX, vector.mY - anotherVector.mY, vector.mZ - anotherVector.mZ);
    }

    template<class Type>
    Vector4<Type> operator * (const Vector4<Type>& vector, Type scalar) noexcept
    {
        return Vector4<Type>(vector.mX * scalar, vector.mY * scalar, vector.mZ * scalar);
    }

    template<class Type>
    bool operator == (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return ( (vector.mX == anotherVector.mX) &&
                 (vector.mY == anotherVector.mY) &&
                 (vector.mZ == anotherVector.mZ) &&
                 (vector.mW == anotherVector.mW) );
    }

    template<class Type>
    bool operator != (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return ( (vector.mX != anotherVector.mX) ||
                 (vector.mY != anotherVector.mY) ||
                 (vector.mZ != anotherVector.mZ) || 
                 (vector.mW != anotherVector.mW) );
    }

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int>;

} 
