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
#include "Matrix4x4.hpp"
#include "Constants.hpp"

namespace Math {

    template<class Type>
    void setIdentityMatrix(Matrix4x4<Type>& matrix) noexcept
    {
        static Type identity = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = identity;
    }

    template<class Type>
    void setOrthoMatrix(Matrix4x4<Type>& matrix, Type left, Type right, Type bottom, Type top, Type near, Type far) noexcept
    {
        Type ortho = {
            2 / (right - left), 0.0, 0.0, -(right + left) / (right - left),
            0.0, 2 / (top - bottom), 0.0,  (top + bottom) / (top - bottom),
            0.0, 0.0, 2 / (far - near), -(far + near) / (far - near),
            0.0, 0.0, 0.0, 0.0
        };
        matrix = ortho;
    }

    template<class Type>
    void setPerspectiveMatrix(Matrix4x4<Type>& matrix, Type fov, Type aspect, Type near, Type far) noexcept
    {
        const Type yScale = 1.0 / tan(RADIANS_PER_DEGREE * fov / 2);
        const Type xScale = yScale / aspect;
        const Type difference = near - far;
        Type perspective = {
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, (far + near) / difference, -1,
            0, 0, 2 * far * near / difference, 0
        };
        matrix = perspective;
    }

    template<class Type>
    void setTranslationMatrix(Matrix4x4<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        Type translation = {
            1.0, 0.0, 0.0, vector.x,
            0.0, 1.0, 0.0, vector.y,
            0.0, 0.0, 1.0, vector.z,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = translation;
    }

    template<class Type>
    void setScaleMatrix(Matrix4x4<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        Type scale = {
            vector.x, 0.0, 0.0, 0.0,
            0.0, vector.y, 0.0, 0.0,
            0.0, 0.0, vector.z, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = scale;
    }

    template<class Type>
    void setRotationMatrixByX(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        Type rotation = {
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(angle), -sin(angle), 0.0,
            0.0, sin(angle),  cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

    template<class Type>
    void setRotationMatrixByY(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        Type rotation = {
            cos(angle), 0.0, -sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            sin(angle), 0.0,  cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

    template<class Type>
    void setRotationMatrixByZ(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        Type rotation = {
            cos(angle), -sin(angle), 0.0, 0.0,
            sin(angle), 1.0,  cos(angle), 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

} 
