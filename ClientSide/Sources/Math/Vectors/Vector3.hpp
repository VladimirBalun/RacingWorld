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
#include <cstdint>
#include <utility>
#include <iterator>
#include <xmmintrin.h>

namespace Math {

    template<class Type>
    class Vector3;

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int>;
    
    template<class Type>
    Vector3<Type> operator + (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept;
    template<class Type>
    Vector3<Type> operator - (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept;
    template<class Type>
    Vector3<Type> operator * (const Vector3<Type>& vector, Type scalar) noexcept;
    template<class Type>
    bool operator == (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept;
    template<class Type>
    bool operator != (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept;

    template<class Type>
    class Vector3
    {
    public:
        static const std::uint8_t VECTOR_SIZE = 3;

		Vector3() noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
		}
		Vector3(Vector3&& anotherVector) noexcept
		{
			//mElements = anotherVector.mElements;
			//anotherVector.mElements = nullptr;
		}
		Vector3(const Vector3& anotherVector) noexcept
		{
			// We are using arithmetic types, so assignment and copy have no difference
			for (int i = 0; i < VECTOR_SIZE; mElements[i] = anotherVector.mElements[i], i++) {}
		}
        Vector3(const Type* array) noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
			// We are using arithmetic types, so assignment and copy have no difference 
			for (int i = 0; i < VECTOR_SIZE; mElements[i] = array[i], i++) {}
		}
        Vector3(Type x, Type y, Type z) noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
			mElements[0] = x;
			mElements[1] = y;
			mElements[2] = z;
		}

        Type getX() const noexcept;
        Type getY() const noexcept;
        Type getZ() const noexcept;
        std::size_t getLength() const noexcept;
        void toArray(Type* array) const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;
        void setZ(Type z) noexcept;

        void normalize() noexcept;
        void add(const Vector3& anotherVector) noexcept;
        void sub(const Vector3& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector3& operator = (const Vector3& anotherVector) noexcept;
        Vector3& operator += (const Vector3& anotherVector) noexcept;
        Vector3& operator -= (const Vector3& anotherVector) noexcept;
        Vector3& operator *= (Type scalar) noexcept;
    private:
        Type mElements[VECTOR_SIZE] = { 0 };
    };

    template<class Type>
    Type Vector3<Type>::getX() const noexcept
    {
		return mElements[0];
    }

    template<class Type>
    Type Vector3<Type>::getY() const noexcept
    {
		return mElements[1];
    }

    template<class Type>
    Type Vector3<Type>::getZ() const noexcept
    {
		return mElements[2];
    }

    template<class Type>
    std::size_t Vector3<Type>::getLength() const noexcept
    {
		return static_cast<std::size_t>(sqrt(mElements[0] * mElements[0] + mElements[1] * mElements[1] + mElements[2] * mElements[2]));
    }

    template<class Type>
    void Vector3<Type>::toArray(Type* array) const noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; array[i] = mElements[i], i++) {}
    }

    template<class Type>
    void Vector3<Type>::setX(Type x) noexcept
    {
		mElements[0] = x;
    }

    template<class Type>
    void Vector3<Type>::setY(Type y) noexcept
    {
		mElements[1] = y;
    }

    template<class Type>
    void Vector3<Type>::setZ(Type z) noexcept
    {
		mElements[2] = z;
    }

    template<class Type>
    void Vector3<Type>::normalize() noexcept
    {
        const std::size_t length = getLength();
        if (length != 0)
			for (int i = 0; i < VECTOR_SIZE; mElements[i] /= static_cast<Type>(length), i++) {}
    }

    template<class Type>
    void Vector3<Type>::add(const Vector3& anotherVector) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; mElements[i] += anotherVector.mElements[i], i++) {}
    }

    template<class Type>
    void Vector3<Type>::sub(const Vector3& anotherVector) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; mElements[i] -= anotherVector.mElements[i], i++) {}
    }

    template<class Type>
    void Vector3<Type>::mul(Type scalar) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; mElements[i] *= scalar, i++) {}
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator = (const Vector3& anotherVector) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; mElements[i] = anotherVector.mElements[i], i++) {}
        return *this;
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator += (const Vector3& anotherVector) noexcept
    {
        add(anotherVector);
        return *this;
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator -= (const Vector3& anotherVector) noexcept
    {
        sub(anotherVector);
        return *this;
    }

    template<class Type>
    Vector3<Type>& Vector3<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Vector3<Type> operator + (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
		if constexpr (sizeof(Type) == 4)
		{
			__m128 vector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&vector));
			__m128 avector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&anotherVector));
			Type * result = reinterpret_cast<Type *>(&_mm_add_ps(vector_as_128bit_num, avector_as_128bit_num));
			return Vector3<Type>(result[0], result[1], result[2]);
		}
		else
	        return Vector3<Type>(vector.getX() + anotherVector.getX(), vector.getY() + anotherVector.getY(), vector.getZ() + anotherVector.getZ());
    }

    template<class Type>
    Vector3<Type> operator - (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
		if constexpr (sizeof(Type) == 4)
		{
			__m128 vector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&vector));
			__m128 avector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&anotherVector));
			Type * result = reinterpret_cast<Type *>(&_mm_sub_ps(vector_as_128bit_num, avector_as_128bit_num));
			return Vector3<Type>(result[0], result[1], result[2]);
		}
		else
	        return Vector3<Type>(vector.getX() - anotherVector.getX(), vector.getY() - anotherVector.getY(), vector.getZ() - anotherVector.getZ());
    }

    template<class Type>
    Vector3<Type> operator * (const Vector3<Type>& vector, Type scalar) noexcept
    {
        return Vector3<Type>(vector.getX() * scalar, vector.getY() * scalar, vector.getZ() * scalar);
    }

    template<class Type>
    bool operator == (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return ( (vector.getX() == anotherVector.getX()) &&
                 (vector.getY() == anotherVector.getY()) &&
                 (vector.getZ() == anotherVector.getZ()) );
    }

    template<class Type>
    bool operator != (const Vector3<Type>& vector, const Vector3<Type>& anotherVector) noexcept
    {
        return !(vector == anotherVector);
    }

} 
