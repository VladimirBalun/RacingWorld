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

namespace Math {

    template <typename Type>
    class Vector4
    {
    public:
        Vector4() = default;
        Vector4(Type x, Type y, Type z, Type w)
            : x(x), y(y), z(z), w(w) {}

        Type getX() const noexcept;
        Type getY() const noexcept;
        Type getZ() const noexcept;
        Type getW() const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;
        void setZ(Type z) noexcept;
        void setW(Type w) noexcept;

        void normalize() noexcept;
        std::size_t getLength() const noexcept;
        Type dot(const Vector4& other) noexcept;
        void add(const Vector4& other) noexcept;
        void sub(const Vector4& other) noexcept;
        void mul(Type scalar) noexcept;
    private:
        Type x = 0;
        Type y = 0;
        Type z = 0;
        Type w = 0;
    };

} 

template <typename Type>
Type Math::Vector4<Type>::getX() const noexcept
{
    return x;
}

template <typename Type>
Type Math::Vector4<Type>::getY() const noexcept
{
    return y;
}

template <typename Type>
Type Math::Vector4<Type>::getZ() const noexcept
{
    return z;
}

template <typename Type>
Type Math::Vector4<Type>::getW() const noexcept
{
    return w;
}

template <typename Type>
void Math::Vector4<Type>::setX(Type x) noexcept
{
    this.x = x;
}

template <typename Type>
void Math::Vector4<Type>::setY(Type y) noexcept
{
    this.y = y;
}

template <typename Type>
void Math::Vector4<Type>::setZ(Type z) noexcept
{
    this.z = z;
}

template <typename Type>
void Math::Vector4<Type>::setW(Type w) noexcept
{
    this.w = w;
}

template <typename Type>
void Math::Vector4<Type>::normalize() noexcept
{
    const size_t length = getLength();
    if (length != 0)
    {
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }
}

template <typename Type>
size_t Math::Vector4<Type>::getLength() const noexcept
{
    return sqrt(x*x + y * y + z * z + w * w);
}

template <typename Type>
Type Math::Vector4<Type>::dot(const Vector4& other) noexcept
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

template <typename Type>
void Math::Vector4<Type>::add(const Vector4& other) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}

template <typename Type>
void Math::Vector4<Type>::sub(const Vector4& other) noexcept
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}

template <typename Type>
void Math::Vector4<Type>::mul(Type scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}
