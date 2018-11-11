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
struct Vector4
{

    ValueType x = { 0 };
    ValueType y = { 0 };
    ValueType z = { 0 };
    ValueType w = { 0 };

    explicit Vector4() = default;
    explicit Vector4(ValueType x, ValueType y, ValueType z, ValueType w)
        : x(x), y(y), z(z), w(w) {}

    size_t getLength() const
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    void normalize()
    {
        size_t length = getLength();
        if (length != 0)
        {
            x /= length;
            y /= length;
            z /= length;
            w /= length;
        }
    }

    void add(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    void sub(const Vector4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }

    template <typename ScalarType>
    void mulOnScalar(ScalarType scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }

};

} }
