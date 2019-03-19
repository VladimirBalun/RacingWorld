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

#include "Vectors.hpp"
#include "Constants.hpp"
#include "Matrices/Matrix2x2.hpp"
#include "Matrices/Matrix3x3.hpp"
#include "Matrices/Matrix4x4.hpp"

namespace Math {

    template<typename Type>
    void setIdentityMatrix(Matrix2x2<Type>& matrix) noexcept
    {
        matrix = {
            1.0, 0.0,
            0.0, 1.0
        };
    }

    template<typename Type>
    void setIdentityMatrix(Matrix3x3<Type>& matrix) noexcept
    {
        matrix = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setIdentityMatrix(Matrix4x4<Type>& matrix) noexcept
    {
        matrix = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setOrthoMatrix(Matrix4x4<Type>& matrix, Type left, Type right, Type bottom, Type top, Type znear, Type zfar) noexcept
    {
        matrix = {
            2 / (right - left), 0.0, 0.0, -(right + left) / (right - left),
            0.0, 2 / (top - bottom), 0.0, -(top + bottom) / (top - bottom),
            0.0, 0.0, -2 / (zfar - znear), -(zfar + znear) / (zfar - znear),
            0.0, 0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setPerspectiveMatrix(Matrix4x4<Type>& matrix, Type fov, Type aspect, Type znear, Type zfar) noexcept
    {
        const Type yScale = static_cast<Type>(1.0 / tan(RADIANS_PER_DEGREE * fov / 2));
        const Type xScale = yScale / aspect;
        const Type difference = zfar - znear;
        matrix = {
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, -(zfar + znear) / difference, -2 * zfar * znear / difference,
            0, 0, -1, 0
        };
    }

    template<typename Type>
    void setLookAt(Matrix4x4<Type>& matrix, const Vector3<Type>& eye, const Vector3<Type>& center, const Vector3<Type>& up) noexcept
    {
        Vector3f mz(eye - center);
        mz.normalize();
        Vector3f my(up);
        my.normalize();
        Vector3f mx(cross(my, mz));
        mx.normalize();
        my = cross(mz, mx);
        my.normalize();
        matrix = {
            mx.getX(), mx.getY(), mx.getZ(), -dot(mx, eye),
            my.getX(), my.getY(), my.getZ(), -dot(my, eye),
            mz.getX(), mz.getY(), mz.getZ(), -dot(mz, eye),
            0.0,       0.0,       0.0,       1.0
        };
    }

    template<typename Type>
    void setTranslationMatrix(Matrix4x4<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        matrix = {
            1.0, 0.0, 0.0, vector.getX(),
            0.0, 1.0, 0.0, vector.getY(),
            0.0, 0.0, 1.0, vector.getZ(),
            0.0, 0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setScaleMatrix(Matrix2x2<Type>& matrix, const Vector2<Type>& vector) noexcept
    {
        matrix = {
            vector.getX(), 0.0,
            0.0, vector.getY()
        };
    }

    template<typename Type>
    void setScaleMatrix(Matrix3x3<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        matrix = {
            vector.getX(), 0.0, 0.0,
            0.0, vector.getY(), 0.0,
            0.0, 0.0, vector.getZ()
        };
    }

    template<typename Type>
    void setScaleMatrix(Matrix4x4<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        matrix = {
            vector.getX(), 0.0, 0.0, 0.0,
            0.0, vector.getY(), 0.0, 0.0,
            0.0, 0.0, vector.getZ(), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setRotationMatrix(Matrix2x2<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            angleCosine, -angleSine,
            angleSine, angleCosinus
        };
    }

    template<typename Type>
    void setRotationMatrixByX(Matrix3x3<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            1.0, 0.0, 0.0,
            0.0, angleCosine, -angleSine,
            0.0, angleSine,  angleCosine,
        };
    }

    template<typename Type>
    void setRotationMatrixByY(Matrix3x3<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            angleCosine, 0.0, angleSine,
            0.0, 1.0, 0.0,
            -angleSine, 0.0, angleCosine
        };
    }

    template<typename Type>
    void setRotationMatrixByZ(Matrix3x3<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            angleCosine, -angleSine, 0.0,
            angleSine, angleCosine, 0.0
            0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setRotationMatrixByX(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            1.0, 0.0, 0.0, 0.0,
            0.0, angleCosine, -angleSine, 0.0,
            0.0, angleSine, angleCosine, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setRotationMatrixByY(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            angleCosine, 0.0, angleSine, 0.0,
            0.0, 1.0, 0.0, 0.0,
            -angleSine, 0.0, angleCosine, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
    }

    template<typename Type>
    void setRotationMatrixByZ(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        const Type angleSine = sin(angle);
        const Type angleCosine = cos(angle);
        matrix = {
            angleCosine, -angleSine, 0.0, 0.0,
            angleSine, angleCosine, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
    }

}
