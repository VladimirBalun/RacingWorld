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

#include <utility>
#include <cstdint>

#include "Vector4.hpp"

namespace Math {

    template <typename Type>
    class Matrix4x4 
    { 
    public:
        static const std::uint8_t ROW_SIZE = 4;
        static constexpr std::uint8_t MATRIX_SIZE = ROW_SIZE * ROW_SIZE;

        Matrix4x4() = default;
        Matrix4x4(const Matrix4x4& other);
        Matrix4x4(Matrix4x4&& other);
        Matrix4x4& operator = (const Matrix4x4& other);
        Matrix4x4& operator = (Matrix4x4&& other);

        void transpose() noexcept;
        void sub(const Matrix4x4& other) noexcept;
        void add(const Matrix4x4& other) noexcept;
        Vector4<Type> mul(const Vector4<Type>& vector) noexcept;
    private:
        Type elements[MATRIX_SIZE] = { 0 };
    };

}

template<typename Type>
Math::Matrix4x4<Type>::Matrix4x4(const Matrix4x4& other)
{
    for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
    {
        elements[i] = other.elements[i];
        elements[i + 1] = other.elements[i + 1];
        elements[i + 2] = other.elements[i + 2];
        elements[i + 3] = other.elements[i + 3];
    }
}

template<typename Type>
Math::Matrix4x4<Type>::Matrix4x4(Matrix4x4&& other)
{
    elements = std::move(other.elements);
}

template<typename Type>
Math::Matrix4x4<Type>& Math::Matrix4x4<Type>::operator = (const Matrix4x4& other) 
{
    for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
    {
        elements[i] = other.elements[i];
        elements[i + 1] = other.elements[i + 1];
        elements[i + 2] = other.elements[i + 2];
        elements[i + 3] = other.elements[i + 3];
    }
    return *this;
}

template<typename Type>
Math::Matrix4x4<Type>& Math::Matrix4x4<Type>::operator = (Matrix4x4&& other)
{
    elements = std::move(other.elements);
    return *this;
}

template<typename Type>
void Math::Matrix4x4<Type>::transpose() noexcept
{
    std::uint8_t currentRow = 0;
    Matrix4x4 tmp_matrix(*this);
    for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
    {
        elements[currentRow] = tmp_matrix.elements[i];
        elements[ROW_SIZE + currentRow] = tmp_matrix.elements[i + 1];
        elements[ROW_SIZE + ROW_SIZE + currentRow] = tmp_matrix.elements[i + 2];
        elements[ROW_SIZE + ROW_SIZE + ROW_SIZE + currentRow] = tmp_matrix.elements[i + 3];
        currentRow++;
    }
}

template<typename Type>
void Math::Matrix4x4<Type>::sub(const Matrix4x4& other) noexcept
{
    for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
    {
        elements[i] -= other.elements[i];
        elements[i + 1] -= other.elements[i + 1];
        elements[i + 2] -= other.elements[i + 2];
        elements[i + 3] -= other.elements[i + 3];
    }
}

template<typename Type>
void Math::Matrix4x4<Type>::add(const Matrix4x4& other) noexcept
{
    for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
    {
        elements[i] += other.elements[i];
        elements[i + 1] += other.elements[i + 1];
        elements[i + 2] += other.elements[i + 2];
        elements[i + 3] += other.elements[i + 3];
    }
}

template<typename Type>
Math::Vector4<Type> Math::Matrix4x4<Type>::mul(const Vector4<Type>& vector) noexcept
{
    Vector4<Type> tmpVector = vector;
    tmpVector.x = elements[ROW_SIZE] * vector.x + elements[ROW_SIZE + 1] * vector.y + elements[ROW_SIZE + 2] * vector.z + elements[ROW_SIZE + 3] * vector.w;
    tmpVector.y = elements[ROW_SIZE * 2] * vector.x + elements[ROW_SIZE * 2 + 1] * vector.y + elements[ROW_SIZE * 2 + 2] * vector.z + elements[ROW_SIZE * 2 + 3] * vector.w;
    tmpVector.z = elements[ROW_SIZE * 3] * vector.x + elements[ROW_SIZE * 3 + 1] * vector.y + elements[ROW_SIZE * 3 + 2] * vector.z + elements[ROW_SIZE * 3 + 3] * vector.w;
    tmpVector.w = elements[ROW_SIZE * 4] * vector.x + elements[ROW_SIZE * 4 + 1] * vector.y + elements[ROW_SIZE * 4 + 2] * vector.z + elements[ROW_SIZE * 4 + 3] * vector.w;
    return tmpVector;
}
