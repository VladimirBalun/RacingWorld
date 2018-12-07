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

#include "Vector3.h"
#include "Matrix4x4.h"

namespace Math {

    template <class Type>
    Matrix4x4<Type> get_identity_matrix4x4() noexcept;

    template <class Type, typename NumberType>
    Matrix4x4<Type> get_ortho_matrix4x4(NumberType left, NumberType right, NumberType bottom, NumberType top, NumberType near, NumberType far) noexcept;

    template <class Type>
    Matrix4x4<Type> get_translation_matrix4x4(const Vector3<Type>& vector) noexcept;

    template <class Type>
    Matrix4x4<Type> get_scale_matrix4x4(const Vector3<Type>& vector) noexcept;

    template <class Type, typename AngleType>
    Matrix4x4<Type> get_rotation_matrix4x4_by_x_axis(AngleType angle) noexcept;

    template <class Type, typename AngleType>
    Matrix4x4<Type> get_rotation_matrix4x4_by_y_axis(AngleType angle) noexcept;

    template <class Type, typename AngleType>
    Matrix4x4<Type> get_rotation_matrix4x4_by_z_axis(AngleType angle) noexcept;

} 
