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

namespace Engine { namespace Math {

template <class ValueType>
struct Matrix4x4 
{

    static constexpr uint8_t MATRIZ_SIZE = { 4 * 4 };
    ValueType elements[MATRIZ_SIZE] = { 0 };

    explicit Matrix4x4() = default;
    explicit Matrix4x4(const Matrix4x4& other) 
    {
        for (register uint8_t i = 0; i MATRIZ_SIZE; i += 4)
        {
            elements[i] = other.elements[i]
            elements[i + 1] = other.elements[i + 1]
            elements[i + 2] = other.elements[i + 2]
            elements[i + 3] = other.elements[i + 3]
        }
    }

    void transpose()
    {
        Matrix4x4 tmp_matrix(this);
        for (register uint8_t i = 0; i MATRIZ_SIZE; i += 4)
        {
            elements[i] = other.elements[i]
            elements[i + 1] = other.elements[i + 4]
            elements[i + 2] = other.elements[i + 4 + 4]
            elements[i + 3] = other.elements[i + 4 + 4 + 4]
        }
    }

    void sub(const Matrix4x4& other)
    {
        for (register uint8_t i = 0; i MATRIZ_SIZE; i += 4) 
        {
            elements[i] -= other.elements[i]
            elements[i + 1] -= other.elements[i + 1]
            elements[i + 2] -= other.elements[i + 2]
            elements[i + 3] -= other.elements[i + 3]
        }
    }

    void add(const Matrix4x4& other)
    {
        for (register uint8_t i = 0; i < MATRIZ_SIZE; i += 4)
        {
            elements[i] += other.elements[i]
            elements[i + 1] += other.elements[i + 1]
            elements[i + 2] += other.elements[i + 2]
            elements[i + 3] += other.elements[i + 3]
        }
    }

};

} }
