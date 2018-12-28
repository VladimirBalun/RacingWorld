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

    template <class Type>
    class Vector2
    {
    public:
        Vector2() = default;
        Vector2(Type x, Type y)
            : x(x), y(y) {}

        Type getX() const noexcept;
        Type getY() const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;

        void normalize() noexcept;
        std::size_t getLength() const noexcept;
        Type dot(const Vector2& other) noexcept;
        void add(const Vector2& other) noexcept;
        void sub(const Vector2& other) noexcept;
        void mul(Type scalar) noexcept;
    private:        
        Type x = 0;
        Type y = 0;
    };

}

template <class Type>
Type Math::Vector2<Type>::getX() const noexcept
{
    return x;
}

template <class Type>
Type Math::Vector2<Type>::getY() const noexcept
{
    return y;
}

template <class Type>
void Math::Vector2<Type>::setX(Type x) noexcept
{
    this.x = x;
}

template <class Type>
void Math::Vector2<Type>::setY(Type y) noexcept
{
    this.y = y;
}

template <class Type>
void Math::Vector2<Type>::normalize() noexcept
{
    const size_t length = getLength();
    if (length != 0)
    {
        x /= length;
        y /= length;
    }
}

template <class Type>
size_t Math::Vector2<Type>::getLength() const noexcept
{
    return sqrt(x*x + y * y);
}

template <class Type>
Type Math::Vector2<Type>::dot(const Vector2& other) noexcept
{
    return x * other.x + y * other.y;
}

template <class Type>
void Math::Vector2<Type>::add(const Vector2& other) noexcept
{
    x += other.x;
    y += other.y;
}

template <class Type>
void Math::Vector2<Type>::sub(const Vector2& other) noexcept
{
    x -= other.x;
    y -= other.y;
}

template <class Type>
void Math::Vector2<Type>::mul(Type scalar) noexcept
{
    x *= scalar;
    y *= scalar;
}
