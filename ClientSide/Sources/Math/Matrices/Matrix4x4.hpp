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

#include "../Vectors/Vector4.hpp"

namespace Math {

    template<class Type>
    class Matrix4x4;

    using Matrix4x4f = Matrix4x4<float>;
    using Matrix4x4d = Matrix4x4<double>;

    template<typename Type>
    const Matrix4x4<Type> operator - (const Matrix4x4<Type>& lhs, const Matrix4x4<Type>& rhs) noexcept;
    template<typename Type>
    Matrix4x4<Type> operator + (const Matrix4x4<Type>& lhs, const Matrix4x4<Type>& rhs) noexcept;
    template<typename Type>
    Matrix4x4<Type> operator * (const Matrix4x4<Type>& lhs, Type rhs) noexcept;
    template<typename Type>
    Matrix4x4<Type> operator * (const Matrix4x4<Type>& lhs, const Vector4<Type>& rhs) noexcept;
    template<typename Type>
    Matrix4x4<Type> operator * (const Matrix4x4<Type>& lhs, const Matrix4x4<Type>& rhs) noexcept;

    template<class Type>
    class Matrix4x4 
    { 
    public:
        static const std::uint8_t ROW_SIZE = 4;
        static const std::uint8_t MATRIX_SIZE = ROW_SIZE * ROW_SIZE;

        explicit Matrix4x4() noexcept = default;
        explicit Matrix4x4(const Type (&array)[MATRIX_SIZE]) noexcept;
        explicit Matrix4x4(const Matrix4x4& anotherMatrix) noexcept;
        explicit Matrix4x4(Matrix4x4&& anotherMatrix) noexcept;

        void transpose() noexcept;
        void sub(const Matrix4x4& anotherMatrix) noexcept;
        void add(const Matrix4x4& anotherMatrix) noexcept;
        void mul(Type scalar) noexcept;
        void mul(const Matrix4x4& anotherMatrix) noexcept;
        Vector4<Type> mul(const Vector4<Type>& vector) noexcept;
        void toArray(Type* array) const;

        Matrix4x4& operator = (const Type (&array)[MATRIX_SIZE]) noexcept;
        Matrix4x4& operator = (const Matrix4x4& anotherMatrix) noexcept;
        Matrix4x4& operator = (Matrix4x4&& anotherMatrix) noexcept;
        Type operator [] (std::uint8_t index) const noexcept;
        Matrix4x4& operator += (const Matrix4x4& anotherMatrix) noexcept;
        Matrix4x4& operator -= (const Matrix4x4& anotherMatrix) noexcept;
        Matrix4x4& operator *= (Type scalar) noexcept;
        Matrix4x4& operator *= (const Vector4<Type>& vector) noexcept;
        Matrix4x4& operator *= (const Matrix4x4& anotherMatrix) noexcept;
    private:
        static const std::uint8_t FIRST_ROW = 0;
        static const std::uint8_t SECOND_ROW = ROW_SIZE;
        static const std::uint8_t THIRD_ROW = ROW_SIZE + ROW_SIZE;
        static const std::uint8_t FOURTH_ROW = ROW_SIZE + ROW_SIZE + ROW_SIZE;
    private:
        Type mElements[MATRIX_SIZE] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    template<class Type>
    Matrix4x4<Type>::Matrix4x4(const Type (&array)[MATRIX_SIZE]) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = array[i];
            mElements[i + 1] = array[i + 1];
            mElements[i + 2] = array[i + 2];
            mElements[i + 3] = array[i + 3];
        }
    }

    template<class Type>
    Matrix4x4<Type>::Matrix4x4(const Matrix4x4& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = otherElements[i];
            mElements[i + 1] = otherElements[i + 1];
            mElements[i + 2] = otherElements[i + 2];
            mElements[i + 3] = otherElements[i + 3];
        }
    }

    template<class Type>
    Matrix4x4<Type>::Matrix4x4(Matrix4x4&& anotherMatrix) noexcept
    {
        std::move(std::begin(anotherMatrix.mElements), std::end(anotherMatrix.mElements), std::begin(mElements));
    }

    template<class Type>
    void Matrix4x4<Type>::transpose() noexcept
    {
        const Matrix4x4 matrix(*this);
        const Type* otherElements = matrix.mElements;
        for (std::uint8_t i col = 0; col < SIZE_ROW; col++) {
            for (std::uint8_t i row = 0; row < SIZE_MATRIX; row += SIZE_ROW) {
                mElements[FIRST_ROW + col] = otherElements[row];
                mElements[SECOND_ROW + col] = otherElements[row + 1];
                mElements[THIRD_ROW + col] = otherElements[row + 2];
                mElements[FOURTH_ROW + col] = otherElements[row + 3];
            }
        }
    }

    template<class Type>
    void Matrix4x4<Type>::sub(const Matrix4x4& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] -= otherElements[i];
            mElements[i + 1] -= otherElements[i + 1];
            mElements[i + 2] -= otherElements[i + 2];
            mElements[i + 3] -= otherElements[i + 3];
        }
    }

    template<class Type>
    void Matrix4x4<Type>::add(const Matrix4x4& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] += otherElements[i];
            mElements[i + 1] += otherElements[i + 1];
            mElements[i + 2] += otherElements[i + 2];
            mElements[i + 3] += otherElements[i + 3];
        }
    }

    template<class Type>
    void Matrix4x4<Type>::mul(Type scalar) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] *= scalar;
            mElements[i + 1] *= scalar;
            mElements[i + 2] *= scalar;
            mElements[i + 3] *= scalar;
        }
    }

    template<class Type>
    void Matrix4x4<Type>::toArray(Type* array) const
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            array[i] = mElements[i];
            array[i + 1] = mElements[i + 1];
            array[i + 2] = mElements[i + 2];
            array[i + 3] = mElements[i + 3];
        }
    }

    template<class Type>
    void Matrix4x4<Type>::mul(const Matrix4x4& anotherMatrix) noexcept
    {
        Type currentElements[MATRIX_SIZE];
        std::copy(std::begin(mElements), std::end(mElements), currentElements);
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE) 
        {
            mElements[i] = currentElements[i] * otherElements[FIRST_ROW] +
                currentElements[i + 1] * otherElements[SECOND_ROW] +
                currentElements[i + 2] * otherElements[THIRD_ROW] +
                currentElements[i + 3] * otherElements[FOURTH_ROW];
            mElements[i + 1] = currentElements[i] * otherElements[FIRST_ROW + 1] +
                currentElements[i + 1] * otherElements[SECOND_ROW + 1] +
                currentElements[i + 2] * otherElements[THIRD_ROW + 1] +
                currentElements[i + 3] * otherElements[FOURTH_ROW + 1];
            mElements[i + 2] = currentElements[i] * otherElements[FIRST_ROW + 2] +
                currentElements[i + 1] * otherElements[SECOND_ROW + 2] +
                currentElements[i + 2] * otherElements[THIRD_ROW + 2] +
                currentElements[i + 3] * otherElements[FOURTH_ROW + 2];
            mElements[i + 3] = currentElements[i] * otherElements[FIRST_ROW + 3] +
                currentElements[i + 1] * otherElements[SECOND_ROW + 3] +
                currentElements[i + 2] * otherElements[THIRD_ROW + 3] +
                currentElements[i + 3] * otherElements[FOURTH_ROW + 3];
        }
    }

    template<class Type>
    Vector4<Type> Matrix4x4<Type>::mul(const Vector4<Type>& vector) noexcept
    {
        Vector4<Type> tmpVector(vector);
        tmpVector.setX(mElements[FIRST_ROW]*vector.getX() + mElements[FIRST_ROW + 1]*vector.getY() + mElements[FIRST_ROW + 2]*vector.getZ());
        tmpVector.setY(mElements[SECOND_ROW]*vector.getX() + mElements[SECOND_ROW + 1]*vector.getY() + mElements[SECOND_ROW + 2]*vector.getZ());
        tmpVector.setZ(mElements[THIRD_ROW]*vector.getX() + mElements[THIRD_ROW + 1]*vector.getY() + mElements[THIRD_ROW + 2]*vector.getZ());
        tmpVector.setW(mElements[FOURTH_ROW]*vector.getX() + mElements[FOURTH_ROW + 1]*vector.getY() + mElements[FOURTH_ROW + 2]*vector.getZ());
        return tmpVector;
    }

    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator = (const Type (&array)[MATRIX_SIZE]) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = array[i];
            mElements[i + 1] = array[i + 1];
            mElements[i + 2] = array[i + 2];
            mElements[i + 3] = array[i + 3];
        }
        return *this;
    }

    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator = (const Matrix4x4& other) noexcept
    {
        const Type* other_elements = other.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = other_elements[i];
            mElements[i + 1] = other_elements[i + 1];
            mElements[i + 2] = other_elements[i + 2];
            mElements[i + 3] = other_elements[i + 3];
        }
        return *this;
    }

    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator = (Matrix4x4&& other) noexcept
    {
        std::move(std::begin(other.mElements), std::end(other.mElements), std::begin(mElements));
        return *this;
    }

    template<class Type>
    Type Matrix4x4<Type>::operator [] (std::uint8_t index) const noexcept
    {
        return mElements[index];
    }

    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator += (const Matrix4x4& other) noexcept
    {
        add(other);
        return *this;
    }

    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator -= (const Matrix4x4& other) noexcept
    {
        sub(other);
        return *this;
    }
    
    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator *= (const Vector4<Type>& vector) noexcept
    {
        mul(vector);
        return *this;
    }
    
    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Matrix4x4<Type>& Matrix4x4<Type>::operator *= (const Matrix4x4& anotherMatrix) noexcept
    {
        mul(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix4x4<Type> operator + (const Matrix4x4<Type>& lhs, const Matrix4x4<Type>& rhs) noexcept
    {
        Matrix4x4<Type> new_matrix(lhs);
        new_matrix.add(rhs);
        return new_matrix;
    }

    template<class Type>
    const Matrix4x4<Type> operator - (const Matrix4x4<Type>& lhs, const Matrix4x4<Type>& rhs) noexcept
    {
        Matrix4x4<Type> new_matrix(lhs);
        new_matrix.sub(rhs);
        return new_matrix;
    }
 
    template<class Type>
    Matrix4x4<Type> operator * (const Matrix4x4<Type>& lhs, Type rhs) noexcept
    {
        Matrix4x4<Type> new_matrix(lhs);
        new_matrix.mul(rhs);
        return new_matrix;
    }

    template<class Type>
    Matrix4x4<Type> operator * (const Matrix4x4<Type>& lhs, const Vector4<Type>& rhs) noexcept
    {
        Matrix4x4<Type> new_matrix(lhs);
        new_matrix.mul(rhs);
        return new_matrix;
    }

    template<class Type>
    Matrix4x4<Type> operator * (const Matrix4x4<Type>& lhs, const Matrix4x4<Type>& rhs) noexcept
    {
        Matrix4x4<Type> new_matrix(lhs);
        new_matrix.mul(rhs);
        return new_matrix;
    }

}
