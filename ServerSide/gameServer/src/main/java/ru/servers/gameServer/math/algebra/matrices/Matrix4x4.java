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

package ru.servers.gameServer.math.algebra.matrices;

import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;

@ToString
@EqualsAndHashCode
@NoArgsConstructor
public class Matrix4x4 {

    private final short SIZE_ROW = 4;
    private final short SIZE_MATRIX = SIZE_ROW * SIZE_ROW;
    private double[] matrix = new double[SIZE_MATRIX];

    public Matrix4x4(double[] matrix) {
        this.matrix = matrix;
    }

    public void transpose() {
        int currentRow = 0;
        double[] tmpMatrix = matrix.clone();
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW) {
            matrix[currentRow] = tmpMatrix[i];
            matrix[SIZE_ROW + currentRow] = tmpMatrix[i + 1];
            matrix[SIZE_ROW + SIZE_ROW + currentRow] = tmpMatrix[i + 2];
            matrix[SIZE_ROW + SIZE_ROW + SIZE_ROW + currentRow] = tmpMatrix[i + 3];
            currentRow++;
        }
    }

    public void add(Matrix4x4 anotherMatrix) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] += anotherMatrix.matrix[i];
            matrix[i + 1] += anotherMatrix.matrix[i + 1];
            matrix[i + 2] += anotherMatrix.matrix[i + 2];
            matrix[i + 3] += anotherMatrix.matrix[i + 3];
        }
    }

    public void sub(Matrix4x4 anotherMatrix) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] -= anotherMatrix.matrix[i];
            matrix[i + 1] -= anotherMatrix.matrix[i + 1];
            matrix[i + 2] -= anotherMatrix.matrix[i + 2];
            matrix[i + 3] -= anotherMatrix.matrix[i + 3];
        }
    }

    public void mul(double number) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] *= number;
            matrix[i + 1] *= number;
            matrix[i + 2] *= number;
            matrix[i + 3] *= number;
        }
    }

    public void mul(Matrix4x4 matrix) {
        // TODO: Write multiplication of matrices
    }

    public double[] toArray() {
        return matrix;
    }

}
