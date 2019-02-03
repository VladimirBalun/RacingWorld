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

#include <utility>
#include <cstdint>

#include "../Vectors/Vector3.hpp"

namespace Math {

    template<class Type>
    class Matrix3x3
    {
    public:
        static const std::uint8_t ROW_SIZE = 3;
        static const std::uint8_t MATRIX_SIZE = ROW_SIZE * ROW_SIZE;

        Matrix3x3() = default;
        Matrix3x3(const Type* array);
        Matrix3x3(const Matrix3x3& anotherMatrix);
        Matrix3x3(Matrix3x3&& anotherMatrix);

        void transpose() noexcept;
        void sub(const Matrix3x3& anotherMatrix) noexcept;
        void add(const Matrix3x3& anotherMatrix) noexcept;
        void mul(Type scalar) noexcept;
        void mul(const Matrix3x3& anotherMatrix) noexcept;
        Vector3<Type> mul(const Vector3<Type>& vector) noexcept;
        void toArray(Type* array) const;

        Matrix3x3& operator = (const Type* array);
        Matrix3x3& operator = (const Matrix3x3& anotherMatrix) noexcept;
        Matrix3x3& operator = (Matrix3x3&& anotherMatrix) noexcept;
        Type operator [] (std::uint8_t index) const;
        Matrix3x3& operator += (const Matrix3x3& anotherMatrix) noexcept;
        Matrix3x3& operator -= (const Matrix3x3& anotherMatrix) noexcept;
        Matrix3x3& operator *= (Type scalar) noexcept;
        Matrix3x3& operator *= (const Vector3<Type>& vector) noexcept;
        Matrix3x3& operator *= (const Matrix3x3& anotherMatrix) noexcept;
    private:
        static const std::uint8_t FIRST_ROW = 0;
        static const std::uint8_t SECOND_ROW = ROW_SIZE;
        static const std::uint8_t THIRD_ROW = ROW_SIZE + ROW_SIZE;
        static const std::uint8_t FOURTH_ROW = ROW_SIZE + ROW_SIZE + ROW_SIZE;
    private:
        Type mElements[MATRIX_SIZE] = { 
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };
    };

    template<class Type>
    Matrix3x3<Type> operator + (const Matrix3x3<Type>& matrix, const Matrix3x3<Type>& anotherMatrix) noexcept;
    template<class Type>
    Matrix3x3<Type> operator - (const Matrix3x3<Type>& matrix, const Matrix3x3<Type>& anotherMatrix) noexcept;
    template<class Type>
    Matrix3x3<Type> operator * (const Matrix3x3<Type>& matrix, Type scalar) noexcept;
    template<class Type>
    Matrix3x3<Type> operator * (const Matrix3x3<Type>& matrix, const Vector3<Type>& vector) noexcept;
    template<class Type>
    Matrix3x3<Type> operator * (const Matrix3x3<Type>& matrix, const Matrix3x3<Type>& anotherMatrix) noexcept;

    using Matrix3x3f = Matrix3x3<float>;
    using Matrix3x3d = Matrix3x3<double>;

    template<class Type>
    Matrix3x3<Type>::Matrix3x3(const Type* array)
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = array[i];
            mElements[i + 1] = array[i + 1];
            mElements[i + 2] = array[i + 2];
        }
    }

    template<class Type>
    Matrix3x3<Type>::Matrix3x3(const Matrix3x3& anotherMatrix)
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = otherElements[i];
            mElements[i + 1] = otherElements[i + 1];
            mElements[i + 2] = otherElements[i + 2];
        }
    }

    template<class Type>
    Matrix3x3<Type>::Matrix3x3(Matrix3x3&& anotherMatrix)
    {
        std::move(std::begin(anotherMatrix.mElements), std::end(anotherMatrix.mElements), std::begin(mElements));
    }

    template<class Type>
    void Matrix3x3<Type>::transpose() noexcept
    {
        const Matrix3x3 matrix(*this);
        const Type* otherElements = matrix.mElements;
        for (std::uint8_t i col = 0; col < SIZE_ROW; col++) {
            for (std::uint8_t i row = 0; row < SIZE_MATRIX; row += SIZE_ROW) {
                mElements[FIRST_ROW + col] = otherElements[row];
                mElements[SECOND_ROW + col] = otherElements[row + 1];
                mElements[THIRD_ROW + col] = otherElements[row + 2];
            }
        }
    }

    template<class Type>
    void Matrix3x3<Type>::sub(const Matrix3x3& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] -= otherElements[i];
            mElements[i + 1] -= otherElements[i + 1];
            mElements[i + 2] -= otherElements[i + 2];
        }
    }

    template<class Type>
    void Matrix3x3<Type>::add(const Matrix3x3& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] += otherElements[i];
            mElements[i + 1] += otherElements[i + 1];
            mElements[i + 2] += otherElements[i + 2];
        }
    }

    template<class Type>
    void Matrix3x3<Type>::mul(Type scalar) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] *= scalar;
            mElements[i + 1] *= scalar;
            mElements[i + 2] *= scalar;
        }
    }

    template<class Type>
    void Matrix3x3<Type>::mul(const Matrix3x3& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = mElements[i]*otherElements[FIRST_ROW] + mElements[i + 1]*otherElements[SECOND_ROW] + mElements[i + 2]*otherElements[THIRD_ROW];
            mElements[i + 1] = mElements[i]*otherElements[FIRST_ROW + 1] + mElements[i + 1]*otherElements[SECOND_ROW + 1] + mElements[i + 2]*otherElements[THIRD_ROW + 1];
            mElements[i + 2] = mElements[i]*otherElements[FIRST_ROW + 2] + mElements[i + 1]*otherElements[SECOND_ROW + 2] + mElements[i + 2]*otherElements[THIRD_ROW + 2];
        }
    }

    template<class Type>
    Vector3<Type> Matrix3x3<Type>::mul(const Vector3<Type>& vector) noexcept
    {
        Vector3<Type> tmpVector(vector);
        tmpVector.setX(mElements[FIRST_ROW]*vector.getX() + mElements[FIRST_ROW + 1]*vector.getY() + mElements[FIRST_ROW + 2]*vector.getZ());
        tmpVector.setY(mElements[SECOND_ROW]*vector.getX() + mElements[SECOND_ROW + 1]*vector.getY() + mElements[SECOND_ROW + 2]*vector.getZ());
        tmpVector.setZ(mElements[THIRD_ROW]*vector.getX() + mElements[THIRD_ROW + 1]*vector.getY() + mElements[THIRD_ROW + 2]*vector.getZ());
        return tmpVector;
    }

    template<class Type>
    void Matrix3x3<Type>::toArray(Type* array) const
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            array[i] = mElements[i];
            array[i + 1] = mElements[i + 1];
            array[i + 2] = mElements[i + 2];
        }
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator = (const Type* array)
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = array[i];
            mElements[i + 1] = array[i + 1];
            mElements[i + 2] = array[i + 2];
        }
        return *this;
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator = (const Matrix3x3& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = otherElements[i];
            mElements[i + 1] = otherElements[i + 1];
            mElements[i + 2] = otherElements[i + 2];
        }
        return *this;
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator = (Matrix3x3&& anotherMatrix) noexcept
    {
        std::move(std::begin(anotherMatrix.mElements), std::end(anotherMatrix.mElements), std::begin(mElements));
        return *this;
    }

    template<class Type>
    Type Matrix3x3<Type>::operator [] (std::uint8_t index) const
    {
        if (index < MATRIX_SIZE)
            return mElements[index];
        else
            throw std::overflow_error("Matrix dows not contain element with current index.");
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator += (const Matrix3x3& anotherMatrix) noexcept
    {
        add(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator -= (const Matrix3x3& anotherMatrix) noexcept
    {
        sub(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator *= (const Vector3<Type>& vector) noexcept
    {
        mul(vector);
        return *this;
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator *= (const Matrix3x3& anotherMatrix) noexcept
    {
        mul(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix3x3<Type> operator + (const Matrix3x3<Type>& matrix, const Matrix3x3<Type>& anotherMatrix) noexcept
    {
        Matrix3x3<Type> newMatrix(matrix);
        newMatrix.add(anotherMatrix);
        return newMatrix;
    }

    template<class Type>
    Matrix3x3<Type> operator - (const Matrix3x3<Type>& matrix, const Matrix3x3<Type>& anotherMatrix) noexcept
    {
        Matrix3x3<Type> newMatrix(matrix);
        newMatrix.sub(anotherMatrix);
        return newMatrix;
    }

    template<class Type>
    Matrix3x3<Type> operator * (const Matrix3x3<Type>& matrix, Type scalar) noexcept
    {
        Matrix3x3<Type> newMatrix(matrix);
        newMatrix.mul(scalar);
        return newMatrix;
    }

    template<class Type>
    Matrix3x3<Type> operator * (const Matrix3x3<Type>& matrix, const Vector3<Type>& vector) noexcept
    {
        Matrix3x3<Type> newMatrix(matrix);
        newMatrix.mul(vector);
        return newMatrix;
    }

    template<class Type>
    Matrix3x3<Type> operator * (const Matrix3x3<Type>& matrix, const Matrix3x3<Type>& anotherMatrix) noexcept 
    {
        Matrix3x3<Type> newMatrix(matrix);
        newMatrix.mul(anotherMatrix);
        return newMatrix;
    }

}