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

#include "Vector3.hpp"

template <class Type>
Type& Math::Vector3<Type>::getX() noexcept
{
    return x;
}

template <class Type>
Type& Math::Vector3<Type>::getY() noexcept
{
    return y;
}

template <class Type>
Type& Math::Vector3<Type>::getZ() noexcept
{
    return z;
}

template <class Type>
Type Math::Vector3<Type>::getX() const noexcept
{
    return x;
}

template <class Type>
Type Math::Vector3<Type>::getY() const noexcept
{
    return y;
}

template <class Type>
Type Math::Vector3<Type>::getZ() const noexcept
{
    return z;
}

template <class Type>
void Math::Vector3<Type>::setX(Type x) noexcept
{
    this.x = x;
}

template <class Type>
void Math::Vector3<Type>::setY(Type y) noexcept
{
    this.y = y;
}

template <class Type>
void Math::Vector3<Type>::setZ(Type z) noexcept
{
    this.z = z;
}

template <class Type>
void Math::Vector3<Type>::normalize() noexcept
{
    const size_t length = getLength();
    if (length != 0)
    {
        x /= length;
        y /= length;
        z /= length;
    }
}

template <class Type>
size_t Math::Vector3<Type>::getLength() const noexcept
{
    return sqrt(x*x + y * y + z * z);
}

template <class Type>
Type Math::Vector3<Type>::dot(const Vector3& other) noexcept
{
    return x*other.x + y*other.y + z*other.z;
}

template <class Type>
void Math::Vector3<Type>::add(const Vector3& other) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
}

template <class Type>
void Math::Vector3<Type>::sub(const Vector3& other) noexcept
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

template <class Type>
void Math::Vector3<Type>::mul(Type scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}
