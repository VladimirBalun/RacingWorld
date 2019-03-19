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

#include "../Vectors/Vector2.hpp"

namespace Math {

    template<class Type>
    class Matrix2x2
    {
    public:
        static const std::uint8_t ROW_SIZE = 2;
        static const std::uint8_t MATRIX_SIZE = ROW_SIZE * ROW_SIZE;

        explicit Matrix2x2() noexcept = default;
        explicit Matrix2x2(const Type (&array)[MATRIX_SIZE]) noexcept;
        explicit Matrix2x2(const Matrix2x2& anotherMatrix) noexcept;
        explicit Matrix2x2(Matrix2x2&& anotherMatrix) noexcept;

        void transpose() noexcept;
        void sub(const Matrix2x2& anotherMatrix) noexcept;
        void add(const Matrix2x2& anotherMatrix) noexcept;
        void mul(Type scalar) noexcept;
        void mul(const Matrix2x2& anotherMatrix) noexcept;
        Vector2<Type> mul(const Vector2<Type>& vector) noexcept;
        void toArray(Type* array) const noexcept;

        Matrix2x2& operator = (const Type (&array)[MATRIX_SIZE]) noexcept;
        Matrix2x2& operator = (const Matrix2x2& anotherMatrix) noexcept;
        Matrix2x2& operator = (Matrix2x2&& anotherMatrix) noexcept;
        Type operator [] (std::uint8_t index) const noexcept;
        Matrix2x2& operator += (const Matrix2x2& anotherMatrix) noexcept;
        Matrix2x2& operator -= (const Matrix2x2& anotherMatrix) noexcept;
        Matrix2x2& operator *= (Type scalar) noexcept;
        Matrix2x2& operator *= (const Vector2<Type>& vector) noexcept;
        Matrix2x2& operator *= (const Matrix2x2& anotherMatrix) noexcept;
    private:
        static const std::uint8_t FIRST_ROW = 0;
        static const std::uint8_t SECOND_ROW = ROW_SIZE;
    private:
        Type mElements[MATRIX_SIZE] = {
            1, 0,
            0, 1
        };
    };

    template<class Type>
    Matrix2x2<Type> operator + (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept;
    template<class Type>
    Matrix2x2<Type> operator - (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept;
    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, Type scalar) noexcept;
    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, const Vector2<Type>& vector) noexcept;
    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept;

    using Matrix2x2f = Matrix2x2<float>;
    using Matrix2x2d = Matrix2x2<double>;

    template<class Type>
    Matrix2x2<Type>::Matrix2x2(const Type (&array)[MATRIX_SIZE]) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = array[i];
            mElements[i + 1] = array[i + 1];
        }
    }

    template<class Type>
    Matrix2x2<Type>::Matrix2x2(const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        std::copy(std::begin(otherElements), std::end(otherElements), std::begin(mElements));
    }

    template<class Type>
    Matrix2x2<Type>::Matrix2x2(Matrix2x2&& anotherMatrix) noexcept
    {
        std::move(std::begin(anotherMatrix.mElements), std::end(anotherMatrix.mElements), std::begin(mElements));
    }

    template<class Type>
    void Matrix2x2<Type>::transpose() noexcept
    {
        const Matrix2x2 matrix(*this);
        const Type* otherElements = matrix.mElements;
        for (std::uint8_t i col = 0; col < SIZE_ROW; col++) {
            for (std::uint8_t i row = 0; row < SIZE_MATRIX; row += SIZE_ROW) {
                mElements[FIRST_ROW + col] = otherElements[row];
                mElements[SECOND_ROW + col] = otherElements[row + 1];
            }
        }
    }

    template<class Type>
    void Matrix2x2<Type>::sub(const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] -= otherElements[i];
            mElements[i + 1] -= otherElements[i + 1];
        }
    }

    template<class Type>
    void Matrix2x2<Type>::add(const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] += otherElements[i];
            mElements[i + 1] += otherElements[i + 1];
        }
    }

    template<class Type>
    void Matrix2x2<Type>::mul(Type scalar) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] *= scalar;
            mElements[i + 1] *= scalar;
        }
    }

    template<class Type>
    void Matrix2x2<Type>::toArray(Type* array) const noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            array[i] = mElements[i];
            array[i + 1] = mElements[i + 1];
        }
    }

    template<class Type>
    void Matrix2x2<Type>::mul(const Matrix2x2& anotherMatrix) noexcept
    {
        Type currentElements[MATRIX_SIZE];
        std::copy(std::begin(mElements), std::end(mElements), currentElements);
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = currentElements[i]*otherElements[FIRST_ROW] + currentElements[i + 1]*otherElements[SECOND_ROW];
            mElements[i + 1] = currentElements[i]*otherElements[FIRST_ROW + 1] + currentElements[i + 1]*otherElements[SECOND_ROW + 1];
        }
    }

    template<class Type>
    Vector2<Type> Matrix2x2<Type>::mul(const Vector2<Type>& vector) noexcept
    {
        Vector2<Type> tmpVector(vector);
        tmpVector.setX(mElements[FIRST_ROW] * vector.getX() + mElements[FIRST_ROW + 1] * vector.getY());
        tmpVector.setY(mElements[SECOND_ROW] * vector.getX() + mElements[SECOND_ROW + 1] * vector.getY());
        return tmpVector;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator = (const Type (&array)[MATRIX_SIZE]) noexcept
    {
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = array[i];
            mElements[i + 1] = array[i + 1];
        }
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator = (const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = otherElements[i];
            mElements[i + 1] = otherElements[i + 1];
        }
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator = (Matrix2x2&& anotherMatrix) noexcept
    {
        std::move(std::begin(anotherMatrix.mElements), std::end(anotherMatrix.mElements), std::begin(mElements));
        return *this;
    }

    template<class Type>
    Type Matrix2x2<Type>::operator [] (std::uint8_t index) const noexcept
    {
        return mElements[index];
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator += (const Matrix2x2& anotherMatrix) noexcept
    {
        add(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator -= (const Matrix2x2& anotherMatrix) noexcept
    {
        sub(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator *= (const Vector2<Type>& vector) noexcept
    {
        mul(vector);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator *= (const Matrix2x2& anotherMatrix) noexcept
    {
        mul(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type> operator + (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.add(anotherMatrix);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator - (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.sub(anotherMatrix);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, Type scalar) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.mul(scalar);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, const Vector2<Type>& vector) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.mul(vector);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept 
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.mul(anotherMatrix);
        return newMatrix;
    }

}
