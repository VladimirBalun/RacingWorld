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

#include "Vector3.hpp"
#include "Matrix3x3.hpp"

namespace Math {

    template<class Type>
    void setIdentityMatrix(Matrix3x3<Type>& matrix) noexcept
    {
        static Type identity[] = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
        };
        matrix = identity;
    }

    template<class Type>
    void setScaleMatrix(Matrix3x3<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        Type scale[] = {
            vector.x, 0.0, 0.0,
            0.0, vector.y, 0.0,
            0.0, 0.0, vector.z
        };
        matrix = scale;
    }

    template<class Type>
    void setRotationMatrixByX(Matrix3x3<Type>& matrix, Type angle) noexcept
    {
        Type rotation[] = {
            1.0, 0.0, 0.0,
            0.0, cos(angle), -sin(angle),
            0.0, sin(angle),  cos(angle),
            0.0, 0.0, 0.0
        };
        matrix = rotation;
    }

    template<class Type>
    void setRotationMatrixByY(Matrix3x3<Type>& matrix, Type angle) noexcept
    {
        Type rotation[] = {
            cos(angle), 0.0, -sin(angle),
            0.0, 1.0, 0.0,
            sin(angle), 0.0,  cos(angle)
        };
        matrix = rotation;
    }

    template<class Type>
    void setRotationMatrixByZ(Matrix3x3<Type>& matrix, Type angle) noexcept
    {
        Type rotation[] = {
            cos(angle), -sin(angle), 0.0,
            sin(angle), 1.0,  cos(angle),
            0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

}