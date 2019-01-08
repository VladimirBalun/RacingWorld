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
    Matrix3x3<Type> getIdentityMatrix3x3() noexcept
    {
        return Matrix3x3<Type>({
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
        });
    }

    template<class Type>
    Matrix3x3<Type> getScaleMatrix3x3(const Vector3<Type>& vector) noexcept
    {
        return Matrix3x3<Type>({
            vector.x, 0.0, 0.0,
            0.0, vector.y, 0.0,
            0.0, 0.0, vector.z
        });
    }

    template<class Type, typename AngleType>
    Matrix3x3<Type> getRotationMatrix3x3ByX(AngleType angle) noexcept
    {
        return Matrix3x3<Type>({
            1.0, 0.0, 0.0,
            0.0, cos(angle), -sin(angle),
            0.0, sin(angle),  cos(angle),
            0.0, 0.0, 0.0
        });
    }

    template<class Type, typename AngleType>
    Matrix3x3<Type> getRotationMatrix3x3ByY(AngleType angle) noexcept
    {
        return Matrix3x3<Type>({
            cos(angle), 0.0, -sin(angle),
            0.0, 1.0, 0.0, 
            sin(angle), 0.0,  cos(angle)
        });
    }

    template<class Type, typename AngleType>
    Matrix3x3<Type> getRotationMatrix3x3ByZ(AngleType angle) noexcept
    {
        return Matrix3x3<Type>({
            cos(angle), -sin(angle), 0.0,
            sin(angle), 1.0,  cos(angle),
            0.0, 0.0, 1.0
        });
    }

}