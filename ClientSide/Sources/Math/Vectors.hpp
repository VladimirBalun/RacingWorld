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

#include "Vectors/Vector2.hpp"
#include "Vectors/Vector3.hpp"
#include "Vectors/Vector4.hpp"

namespace Math {

    template<typename Type>
    Math::Vector2<Type> normalize(const Vector2<Type>& vector) noexcept
    {
        Math::Vector2<Type> normalized_vector = vector;
        normalized_vector.normalize();
        return normalized_vector;
    }

    template<typename Type>
    Math::Vector3<Type> normalize(const Vector3<Type>& vector) noexcept
    {
        Math::Vector3<Type> normalized_vector = vector;
        normalized_vector.normalize();
        return normalized_vector;
    }

    template<typename Type>
    Math::Vector4<Type> normalize(const Vector4<Type>& vector) noexcept
    {
        Math::Vector4<Type> normalized_vector = vector;
        normalized_vector.normalize();
        return normalized_vector;
    }

    template<typename Type>
    Type dot(const Vector2<Type>& vector, const Vector2<Type>& another_vector) noexcept
    {
        return vector.getX()*another_vector.getX() + vector.getY()*another_vector.getY();
    }

    template<typename Type>
    Type dot(const Vector3<Type>& vector, const Vector3<Type>& another_vector) noexcept
    {
        return vector.getX()*another_vector.getX() + vector.getY()*another_vector.getY() + vector.getZ()*another_vector.getZ();
    }

    template<typename Type>
    Type dot(const Vector4<Type>& vector, const Vector4<Type>& another_vector) noexcept
    {
        return vector.getX()*another_vector.getX() + vector.getY()*another_vector.getY() + vector.getZ()*another_vector.getZ();
    }

    template<typename Type>
    Vector3<Type> cross(const Vector3<Type>& vector, const Vector3<Type>& another_vector) noexcept
    {
        const Type x = vector.getY()*another_vector.getZ() - vector.getZ()*another_vector.getY();
        const Type y = -(vector.getX()*another_vector.getZ() - vector.getZ()*another_vector.getX());
        const Type z = vector.getX()*another_vector.getY() - vector.getY()*another_vector.getX();
        return { x, y, z };
    }

    template<typename Type>
    Vector4<Type> cross(const Vector4<Type>& vector, const Vector4<Type>& another_vector) noexcept
    {
        const Type x = vector.getY()*another_vector.getZ() - vector.getZ()*another_vector.getY();
        const Type y = -(vector.getX()*another_vector.getZ() - vector.getZ()*another_vector.getX());
        const Type z = vector.getX()*another_vector.getY() - vector.getY()*another_vector.getX();
        return { x, y, z };
    }

}
