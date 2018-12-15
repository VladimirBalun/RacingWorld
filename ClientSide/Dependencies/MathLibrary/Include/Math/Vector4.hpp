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
    class Vector4
    {
    public:
        Vector4() = default;
        Vector4(Type x, Type y, Type z, Type w)
            : x(x), y(y), z(z), w(w) {}

        Type& getX() noexcept;
        Type& getY() noexcept;
        Type& getZ() noexcept;
        Type& getW() noexcept;

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
