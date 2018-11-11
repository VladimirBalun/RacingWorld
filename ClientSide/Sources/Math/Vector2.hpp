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
#include <type_traits>

namespace Engine { namespace Math {

template <class ValueType>
struct Vector2
{

    ValueType x = { 0 };
    ValueType y = { 0 };

    explicit Vector2() = default;
    explicit Vector2(ValueType x, ValueType y)
        : x(x), y(y) {}

    size_t getLength() const
    {
        return sqrt(x*x + y*y);
    }

    void normalize()
    {
        size_t length = getLength();
        if (length != 0)
        {
            x /= length;
            y /= length;
        }
    }

    void add(const Vector2& other)
    {
        x += other.x;
        y += other.y;
    }

    void sub(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
    }

    template <typename ScalarType>
    void mulOnScalar(ScalarType scalar)
    {
        x *= scalar;
        y *= scalar;
    }

};

} }
