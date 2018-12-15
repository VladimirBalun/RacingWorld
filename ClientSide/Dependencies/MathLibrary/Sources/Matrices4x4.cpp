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

#include "Matrices4x4.hpp"

template <class Type>
Math::Matrix4x4<Type> Math::get_identity_matrix4x4() noexcept
{
    return Matrix4x4<Type>({
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    });
}

template <class Type, typename NumberType>
Math::Matrix4x4<Type> Math::get_ortho_matrix4x4(NumberType left, NumberType right, NumberType bottom, NumberType top, NumberType near, NumberType far) noexcept
{
    return Matrix4x4<Type>({
        2 / (right - left), 0.0, 0.0, -(right + left) / (right - left),
        0.0, 2 / (top - bottom), 0.0,  (top + bottom) / (top - bottom),
        0.0, 0.0, 2 / (far - near), -(far + near) / (far - near),
        0.0, 0.0, 0.0, 0.0
    });
}

template <class Type>
Math::Matrix4x4<Type> Math::get_translation_matrix4x4(const Math::Vector3<Type>& vector) noexcept
{
    return Matrix4x4<Type>({
        1.0, 0.0, 0.0, vector.x,
        0.0, 1.0, 0.0, vector.y,
        0.0, 0.0, 1.0, vector.z,
        0.0, 0.0, 0.0, 1.0
    });
}

template <class Type>
Math::Matrix4x4<Type> Math::get_scale_matrix4x4(const Math::Vector3<Type>& vector) noexcept
{
    return Matrix4x4<Type>({
        vector.x, 0.0, 0.0, 0.0,
        0.0, vector.y, 0.0, 0.0,
        0.0, 0.0, vector.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    });
}

template <class Type, typename AngleType>
Math::Matrix4x4<Type> Math::get_rotation_matrix4x4_by_x_axis(AngleType angle) noexcept
{
    return Matrix4x4<Type>({
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(angle), -sin(angle), 0.0,
        0.0, sin(angle),  cos(angle), 0.0,
        0.0, 0.0, 0.0, 1.0
    });
}

template <class Type, typename AngleType>
Math::Matrix4x4<Type> Math::get_rotation_matrix4x4_by_y_axis(AngleType angle) noexcept
{
    return Matrix4x4<Type>({
        cos(angle), 0.0, -sin(angle), 0.0,
        0.0, 1.0, 0.0, 0.0,
        sin(angle), 0.0,  cos(angle), 0.0,
        0.0, 0.0, 0.0, 1.0
    });
}

template <class Type, typename AngleType>
Math::Matrix4x4<Type> Math::get_rotation_matrix4x4_by_z_axis(AngleType angle) noexcept
{
    return Matrix4x4<Type>({
        cos(angle), -sin(angle), 0.0, 0.0,
        sin(angle), 1.0,  cos(angle), 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    });
}
