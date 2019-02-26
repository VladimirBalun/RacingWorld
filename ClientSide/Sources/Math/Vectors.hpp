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
        Math::Vector2<Type> normalizedVector = vector;
        normalizedVector.normalize();
        return normalizedVector;
    }

    template<typename Type>
    Math::Vector3<Type> normalize(const Vector3<Type>& vector) noexcept
    {
        Math::Vector3<Type> normalizedVector = vector;
        normalizedVector.normalize();
        return normalizedVector;
    }

    template<typename Type>
    Math::Vector4<Type> normalize(const Vector4<Type>& vector) noexcept
    {
        Math::Vector4<Type> normalizedVector = vector;
        normalizedVector.normalize();
        return normalizedVector;
    }

    template<typename Type>
    Type dot(const Vector2<Type>& vector, const Vector2<Type>& anotherVector) noexcept
    {
        return vector.getX()*anotherVector.getX() + vector.getY()*anotherVector.getY();
    }

    template<typename Type>
    Type dot(const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return vector.getX()*anotherVector.getX() + vector.getY()*anotherVector.getY() + vector.getZ()*anotherVector.getZ();
    }

    template<typename Type>
    Type dot(const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return vector.getX()*anotherVector.getX() + vector.getY()*anotherVector.getY() + vector.getZ()*anotherVector.getZ();
    }

    template<typename Type>
    Vector3<Type> cross(const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        const Type x = vector.getY()*anotherVector.getZ() - vector.getZ()*anotherVector.getY();
        const Type y = -(vector.getX()*anotherVector.getZ() - vector.getZ()*anotherVector.getX());
        const Type z = vector.getX()*anotherVector.getY() - vector.getY()*anotherVector.getX();
        return { x, y, z };
    }

    template<typename Type>
    Vector4<Type> cross(const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        const Type x = vector.getY()*anotherVector.getZ() - vector.getZ()*anotherVector.getY();
        const Type y = -(vector.getX()*anotherVector.getZ() - vector.getZ()*anotherVector.getX());
        const Type z = vector.getX()*anotherVector.getY() - vector.getY()*anotherVector.getX();
        return { x, y, z };
    }

}
