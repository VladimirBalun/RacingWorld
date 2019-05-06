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
#include <type_traits>
#include <xmmintrin.h>

namespace Math {

    template<class Type>
    class Vector4;

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int>;

    template<class Type>
    Vector4<Type> operator + (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;
    template<class Type>
    Vector4<Type> operator - (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;
    template<class Type>
    Vector4<Type> operator * (const Vector4<Type>& vector, Type scalar) noexcept;
    template<class Type>
    bool operator == (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;
    template<class Type>
    bool operator != (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept;

    template<class Type>
    class Vector4
    {
    public:
        static const std::uint8_t VECTOR_SIZE = 4;

		Vector4() noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
		}
		Vector4(Vector4&& anotherVector) noexcept
		{
			mElements = anotherVector.mElements;
			anotherVector.mElements = nullptr;
		}
		Vector4(const Vector4& anotherVector) noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
			// We are using arithmetic types, so assignment and copy have no difference
			for (int i = 0; i < VECTOR_SIZE; mElements[i] = anotherVector.mElements[i], i++) {}
		}
        Vector4(const Type* array) noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
			// We are using arithmetic types, so assignment and copy have no difference
			for (int i = 0; i < VECTOR_SIZE; mElements[i] = array[i], i++) {}
		}
        Vector4(Type x, Type y, Type z) noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
			mElements[0] = x;
			mElements[1] = y;
			mElements[2] = z;
			mElements[3] = 1;
		}
        Vector4(Type x, Type y, Type z, Type w) noexcept
		{
			static_assert(std::is_arithmetic_v<Type>, "The \"Type\" must be an integer or a floating point number.");
			mElements[0] = x;
			mElements[1] = y;
			mElements[2] = z;
			mElements[3] = w;
		}

        Type getX() const noexcept;
        Type getY() const noexcept;
        Type getZ() const noexcept;
        Type getW() const noexcept;
        std::size_t getLength() const noexcept;
        void toArray(Type* array) const noexcept;

        void setX(Type x) noexcept;
        void setY(Type y) noexcept;
        void setZ(Type z) noexcept;
        void setW(Type w) noexcept;

        void normalize() noexcept;
        void add(const Vector4& anotherVector) noexcept;
        void sub(const Vector4& anotherVector) noexcept;
        void mul(Type scalar) noexcept;

        Vector4& operator = (const Vector4& anotherVector) noexcept;
        Vector4& operator += (const Vector4& anotherVector) noexcept;
        Vector4& operator -= (const Vector4& anotherVector) noexcept;
        Vector4& operator *= (Type scalar) noexcept;
    private:
		alignas(16) Type mElements[VECTOR_SIZE];
    };

    template<class Type>
    Type Vector4<Type>::getX() const noexcept
    {
        return mElements[0];
    }

    template<class Type>
    Type Vector4<Type>::getY() const noexcept
    {
		return mElements[1];
    }

    template<class Type>
    Type Vector4<Type>::getZ() const noexcept
    {
		return mElements[2];
    }

    template<class Type>
    Type Vector4<Type>::getW() const noexcept
    {
		return mElements[3];
    }

    template<class Type>
    std::size_t Vector4<Type>::getLength() const noexcept
    {
        return static_cast<std::size_t>(sqrt(mElements[0]*mElements[0] + mElements[1]*mElements[1] + mElements[2]*mElements[2]));
    }

    template<class Type>
    void Vector4<Type>::toArray(Type* array) const noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; array[i] = mElements[i], i++) {}
    }

    template<class Type>
    void Vector4<Type>::setX(Type x) noexcept
    {
        mElements[0] = x;
    }

    template<class Type>
    void Vector4<Type>::setY(Type y) noexcept
    {
        mElements[1] = y;
    }

    template<class Type>
    void Vector4<Type>::setZ(Type z) noexcept
    {
        mElements[2] = z;
    }

    template<class Type>
    void Vector4<Type>::setW(Type w) noexcept
    {
        mElements[3] = w;
    }

    template<class Type>
    void Vector4<Type>::normalize() noexcept
    {
        const std::size_t length = getLength();
        if (length != 0)
			for (int i = 0; i < VECTOR_SIZE - 1; mElements[i] /= static_cast<Type>(length), i++) {}
    }

    template<class Type>
    void Vector4<Type>::add(const Vector4& anotherVector) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE - 1; mElements[i] += anotherVector.mElements[i], i++) {}
    }

    template<class Type>
    void Vector4<Type>::sub(const Vector4& anotherVector) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE - 1; mElements[i] -= anotherVector.mElements[i], i++) {}
    }

    template<class Type>
    void Vector4<Type>::mul(Type scalar) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE - 1; mElements[i] *= scalar, i++) {}
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator = (const Vector4& anotherVector) noexcept
    {
		for (int i = 0; i < VECTOR_SIZE; mElements[i] = anotherVector.mElements[i], i++) {}
        return *this;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator += (const Vector4& anotherVector) noexcept
    {
        add(anotherVector);
        return *this;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator -= (const Vector4& anotherVector) noexcept
    {
        sub(anotherVector);
        return *this;
    }

    template<class Type>
    Vector4<Type>& Vector4<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Vector4<Type> operator + (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
		if constexpr (sizeof(Type) == 4)
		{
			__m128 avector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&anotherVector));
			__m128 vector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&vector));
			Type * result = reinterpret_cast<Type *>(&_mm_add_ps(vector_as_128bit_num, avector_as_128bit_num));
			result[3] = 1;
			return Vector4<Type>(result);
		}
		else
			return Vector4<Type>(vector.getX() + anotherVector.getX(), vector.getY() + anotherVector.getY(), vector.getZ() + anotherVector.getZ());
    }

    template<class Type>
    Vector4<Type> operator - (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
		if constexpr (sizeof(Type) == 4)
		{
			__m128 avector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&anotherVector));
			__m128 vector_as_128bit_num = *(reinterpret_cast<const __m128 *>(&vector));
			Type * result = reinterpret_cast<Type *>(&_mm_sub_ps(vector_as_128bit_num, avector_as_128bit_num));
			result[3] = 1;
			return Vector4<Type>(result);
		}
		else
	        return Vector4<Type>(vector.getX() - anotherVector.getX(), vector.getY() - anotherVector.getY(), vector.getZ() - anotherVector.getZ());
    }

    template<class Type>
    Vector4<Type> operator * (const Vector4<Type>& vector, Type scalar) noexcept
    {
		return Vector4<Type>(vector.getX() * scalar, vector.getY() * scalar, vector.getZ() * scalar);
    }

    template<class Type>
    bool operator == (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
		return ( (vector.getX() == anotherVector.getX()) &&
                 (vector.getY() == anotherVector.getY()) &&
                 (vector.getZ() == anotherVector.getZ()) &&
                 (vector.getW() == anotherVector.getW()) );
    }

    template<class Type>
    bool operator != (const Vector4<Type>& vector, const Vector4<Type>& anotherVector) noexcept
    {
        return !(vector == anotherVector);
    }

} 
