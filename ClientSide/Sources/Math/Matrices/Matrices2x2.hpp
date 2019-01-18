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

#include "Matrix2x2.hpp"
#include "Vectors/Vector2.hpp"

namespace Math {

    template<typename Type>
    void setIdentityMatrix(Matrix2x2<Type>& matrix) noexcept
    {
        static Type identity[] = {
            1.0, 0.0,
            0.0, 1.0 
        };
        matrix = identity;
    }

    template<class Type>
    void setScaleMatrix(Matrix2x2<Type>& matrix, const Vector2<Type>& vector) noexcept
    {
        Type scale[] = {
            vector.getX(), 0.0,
            0.0, vector.getY()
        };
        matrix = scale;
    }

    template<class Type>
    void setScaleMatrix(Matrix2x2<Type>& matrix, Type x, Type y) noexcept
    {
        Type scale[] = {
            x, 0.0,
            0.0, y
        };
        matrix = scale;
    }

    template<class Type>
    void setRotationMatrix(Matrix2x2<Type>& matrix, Type angle) noexcept
    {
        Type scale[] = {
            cos(angle), -sin(angle),
            sin(angle), cos(angle)
        };
        matrix = scale;
    }

}
