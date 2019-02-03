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

#include "Matrix4x4.hpp"
#include "../Constants.hpp"
#include "../Vectors/Vector3.hpp"

namespace Math {

    template<typename Type>
    void setIdentityMatrix(Matrix4x4<Type>& matrix) noexcept
    {
        static Type identity[] = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = identity;
    }

    template<typename Type>
    void setOrthoMatrix(Matrix4x4<Type>& matrix, Type left, Type right, Type bottom, Type top, Type znear, Type zfar) noexcept
    {
        Type ortho[] = {
            2 / (right - left), 0.0, 0.0, -(right + left) / (right - left),
            0.0, 2 / (top - bottom), 0.0, -(top + bottom) / (top - bottom),
            0.0, 0.0, -2 / (zfar - znear), -(zfar + znear) / (zfar - znear),
            0.0, 0.0, 0.0, 1.0
        };
        matrix = ortho;
    }

    template<typename Type>
    void setPerspectiveMatrix(Matrix4x4<Type>& matrix, Type fov, Type aspect, Type znear, Type zfar) noexcept
    {
        const Type yScale = static_cast<Type>(1.0 / tan(RADIANS_PER_DEGREE * fov / 2));
        const Type xScale = yScale / aspect;
        const Type difference = znear - zfar;
        Type perspective[] = {
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, (zfar + znear) / difference, 2 * zfar * znear / difference,
            0, 0, -1, 0
        };
        matrix = perspective;

    }

    template<typename Type>
    void setLookAt(Matrix4x4<Type>& matrix, const Vector3<Type> right, const Vector3<Type> up, const Vector3<Type> direction) noexcept
    {
        Type lookAt[] = {
          right.getX(), right.getY(), right.getZ(), 0.0,
          up.getX(), up.getY(), up.getZ(), 0.0,
          direction.getX(), direction.getY(), direction.getZ(), 0.0,
          0.0, 0.0, 0.0, 1.0
        };
        matrix = lookAt;
    }

    template<typename Type>
    void setTranslationMatrix(Matrix4x4<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        Type translation[] = {
            1.0, 0.0, 0.0, vector.getX(),
            0.0, 1.0, 0.0, vector.getY(),
            0.0, 0.0, 1.0, vector.getZ(),
            0.0, 0.0, 0.0, 1.0
        };
        matrix = translation;
    }
    
    template<typename Type>
    void setTranslationMatrix(Matrix4x4<Type>& matrix, Type x, Type y, Type z) noexcept
    {
        Type translation[] = {
            1.0, 0.0, 0.0, x,
            0.0, 1.0, 0.0, y,
            0.0, 0.0, 1.0, z,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = translation;
    }
    
    template<typename Type>
    void setScaleMatrix(Matrix4x4<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        Type scale[] = {
            vector.getX(), 0.0, 0.0, 0.0,
            0.0, vector.getY(), 0.0, 0.0,
            0.0, 0.0, vector.getZ(), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = scale;
    }

    template<typename Type>
    void setScaleMatrix(Matrix4x4<Type>& matrix, Type x, Type y, Type z) noexcept
    {
        Type scale[] = {
            x, 0.0, 0.0, 0.0,
            0.0, y, 0.0, 0.0,
            0.0, 0.0, z, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = scale;
    }

    template<typename Type>
    void setRotationMatrixByX(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        Type rotation[] = {
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(angle), -sin(angle), 0.0,
            0.0, sin(angle),  cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

    template<typename Type>
    void setRotationMatrixByY(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        Type rotation[] = {
            cos(angle), 0.0, sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(angle), 0.0, cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

    template<typename Type>
    void setRotationMatrixByZ(Matrix4x4<Type>& matrix, Type angle) noexcept
    {
        Type rotation[] = {
            cos(angle), -sin(angle), 0.0, 0.0,
            sin(angle),  cos(angle), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        matrix = rotation;
    }

} 
