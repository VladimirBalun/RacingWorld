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

#include "Vector4.h"

template <class Type>
Type& Math::Vector4<Type>::getX() noexcept
{
    return x;
}

template <class Type>
Type& Math::Vector4<Type>::getY() noexcept
{
    return y;
}

template <class Type>
Type& Math::Vector4<Type>::getZ() noexcept
{
    return z;
}

template <class Type>
Type& Math::Vector4<Type>::getW() noexcept
{
    return w;
}

template <class Type>
Type Math::Vector4<Type>::getX() const noexcept
{
    return x;
}

template <class Type>
Type Math::Vector4<Type>::getY() const noexcept
{
    return y;
}

template <class Type>
Type Math::Vector4<Type>::getZ() const noexcept
{
    return z;
}

template <class Type>
Type Math::Vector4<Type>::getW() const noexcept
{
    return w;
}

template <class Type>
void Math::Vector4<Type>::setX(Type x) noexcept
{
    this.x = x;
}

template <class Type>
void Math::Vector4<Type>::setY(Type y) noexcept
{
    this.y = y;
}

template <class Type>
void Math::Vector4<Type>::setZ(Type z) noexcept
{
    this.z = z;
}

template <class Type>
void Math::Vector4<Type>::setW(Type w) noexcept
{
    this.w = w;
}

template <class Type>
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

template <class Type>
size_t Math::Vector4<Type>::getLength() const noexcept
{
    return sqrt(x*x + y * y + z * z + w * w);
}

template <class Type>
Type Math::Vector4<Type>::dot(const Vector4& other) noexcept
{
    return x*other.x + y*other.y + z*other.z + w*other.w;
}

template <class Type>
void Math::Vector4<Type>::add(const Vector4& other) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}

template <class Type>
void Math::Vector4<Type>::sub(const Vector4& other) noexcept
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}

template <class Type>
void Math::Vector4<Type>::mul(Type scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}
