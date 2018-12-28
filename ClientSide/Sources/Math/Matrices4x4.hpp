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

namespace Math {

    template<typename Type>
    Matrix4x4<Type> getIdentityMatrix4x4() noexcept
    {
        return Matrix4x4<Type>({
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
            });
    }

    template<typename Type, typename NumberType>
    Matrix4x4<Type> getOrthoMatrix4x4(NumberType left, NumberType right, NumberType bottom, NumberType top, NumberType near, NumberType far) noexcept
    {
        return Matrix4x4<Type>({
            2 / (right - left), 0.0, 0.0, -(right + left) / (right - left),
            0.0, 2 / (top - bottom), 0.0,  (top + bottom) / (top - bottom),
            0.0, 0.0, 2 / (far - near), -(far + near) / (far - near),
            0.0, 0.0, 0.0, 0.0
            });
    }

    template<typename Type>
    Matrix4x4<Type> getTranslationMatrix4x4(const Vector3<Type>& vector) noexcept
    {
        return Matrix4x4<Type>({
            1.0, 0.0, 0.0, vector.x,
            0.0, 1.0, 0.0, vector.y,
            0.0, 0.0, 1.0, vector.z,
            0.0, 0.0, 0.0, 1.0
            });
    }

    template<typename Type>
    Matrix4x4<Type> getScaleMatrix4x4(const Vector3<Type>& vector) noexcept
    {
        return Matrix4x4<Type>({
            vector.x, 0.0, 0.0, 0.0,
            0.0, vector.y, 0.0, 0.0,
            0.0, 0.0, vector.z, 0.0,
            0.0, 0.0, 0.0, 1.0
            });
    }

    template<typename Type, typename AngleType>
    Matrix4x4<Type> getRotationMatrix4x4ByX(AngleType angle) noexcept
    {
        return Matrix4x4<Type>({
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(angle), -sin(angle), 0.0,
            0.0, sin(angle),  cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
            });
    }

    template<typename Type, typename AngleType>
    Matrix4x4<Type> getRotationMatrix4x4ByY(AngleType angle) noexcept
    {
        return Matrix4x4<Type>({
            cos(angle), 0.0, -sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            sin(angle), 0.0,  cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
            });
    }

    template<typename Type, typename AngleType>
    Matrix4x4<Type> getRotationMatrix4x4ByZ(AngleType angle) noexcept
    {
        return Matrix4x4<Type>({
            cos(angle), -sin(angle), 0.0, 0.0,
            sin(angle), 1.0,  cos(angle), 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
            });
    }

} 
