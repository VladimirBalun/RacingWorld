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

#include "Vector2.hpp"
#include "Matrix2x2.hpp"

namespace Math {

    template<class Type>
    Matrix2x2<Type> getIdentityMatrix2x2() noexcept
    {
        return Matrix2x2<Type>({
            1.0, 0.0
            0.0, 1.0
        });
    }

    template<class Type>
    Matrix2x2<Type> getScaleMatrix2x2(const Vector2<Type>& vector) noexcept
    {
        return Matrix2x2<Type>({
            vector.x, 0.0,
            0.0, vector.y
            });
    }

    template<class Type, typename AngleType>
    Matrix2x2<Type> getRotationMatrix2x2(AngleType angle) noexcept
    {
        return Matrix2x2<Type>({
            cos(angle), -sin(angle),
            sin(angle), cos(angle)
        });
    }

}
