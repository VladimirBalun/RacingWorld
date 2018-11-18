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

#include <cstdint>

#include "Vector4.h"

namespace Math {

    template <class Type>
    struct Matrix4x4 
    { 
        static const std::uint8_t ROW_SIZE = 4;
        static constexpr std::uint8_t MATRIX_SIZE = ROW_SIZE * ROW_SIZE;

        Type elements[MATRIX_SIZE] = { 0 };

        Matrix4x4() = default;
        Matrix4x4(const Matrix4x4& other);
        Matrix4x4(Matrix4x4&& other) 
            : elements(std::move(other.elements)) {}

        void transpose() noexcept;
        void sub(const Matrix4x4& other) noexcept;
        void add(const Matrix4x4& other) noexcept;
        void mul(Vector4<Type>& vector) noexcept;
        void mul(const Matrix4x4& other) noexcept;
    };

}
