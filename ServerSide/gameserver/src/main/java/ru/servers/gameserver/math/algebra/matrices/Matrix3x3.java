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

package ru.servers.gameserver.math.algebra.matrices;

import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Matrix3x3 {

    private static final byte SIZE_ROW = 3;
    private static final byte SIZE_MATRIX = SIZE_ROW * SIZE_ROW;
    private double[] matrix = new double[SIZE_MATRIX];

    public void transpose() {
        double[] tmpMatrix = matrix.clone();
        for (byte col = 0; col < SIZE_ROW; col++){
            for (byte row = 0; row < SIZE_MATRIX; row += SIZE_ROW) {
                matrix[col] = tmpMatrix[row];
                matrix[SIZE_ROW + col] = tmpMatrix[row + 1];
                matrix[SIZE_ROW + SIZE_ROW + col] = tmpMatrix[row + 2];
            }
        }
    }
    public void add(Matrix3x3 another) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] += another.matrix[i];
            matrix[i + 1] += another.matrix[i + 1];
            matrix[i + 2] += another.matrix[i + 2];
        }
    }

    public void sub(Matrix3x3 another) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] -= another.matrix[i];
            matrix[i + 1] -= another.matrix[i + 1];
            matrix[i + 2] -= another.matrix[i + 2];
        }
    }

    public void mul(double number) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] *= number;
            matrix[i + 1] *= number;
            matrix[i + 2] *= number;
        }
    }

    public Vector3 mul(Vector3 vector){
        Vector3 newVector = new Vector3();
        double[] arrayVector = newVector.toArray();
        for (byte i = 0; i < SIZE_ROW; i++) {
            newVector.setX(newVector.getX() + matrix[i]*arrayVector[i]);
            newVector.setY(newVector.getY() + matrix[SIZE_ROW + i]*arrayVector[i]);
            newVector.setZ(newVector.getZ() + matrix[SIZE_ROW + SIZE_ROW + i]*arrayVector[i]);
        }
        return newVector;
    }

    public double[] toArray() {
        return matrix;
    }

}
