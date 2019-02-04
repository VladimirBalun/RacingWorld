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

package ru.servers.game.math.algebra.matrices;

import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;
import ru.servers.game.math.algebra.vectors.Vector2;

@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Matrix2x2 {

    private static final byte SIZE_ROW = 2;
    private static final byte SIZE_MATRIX = SIZE_ROW * SIZE_ROW;
    private double[] matrix = new double[SIZE_MATRIX];

    public void transpose(){
        double[] tmpMatrix = matrix.clone();
        for (byte col = 0; col < SIZE_ROW; col++){
            for (byte row = 0; row < SIZE_MATRIX; row += SIZE_ROW){
                matrix[col] = tmpMatrix[row];
                matrix[SIZE_ROW + col] = tmpMatrix[row + 1];
            }
        }
    }

    public void add(Matrix2x2 another) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] += another.matrix[i];
            matrix[i + 1] += another.matrix[i + 1];
        }
    }

    public void sub(Matrix2x2 another) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW){
            matrix[i] -= another.matrix[i];
            matrix[i + 1] -= another.matrix[i + 1];
        }
    }

    public void mul(double number) {
        for (byte i = 0; i < SIZE_MATRIX; i += SIZE_ROW) {
            matrix[i] *= number;
            matrix[i + 1] *= number;
        }
    }

    public Vector2 mul(Vector2 vector){
        Vector2 newVector = new Vector2();
        double[] vectorArray = vector.toArray();
        for (byte i = 0; i < SIZE_ROW; i++){
            newVector.setX(newVector.getX() + matrix[i]*vectorArray[i]);
            newVector.setY(newVector.getY() + matrix[SIZE_ROW + i]*vectorArray[i]);
        }
        return newVector;
    }

    public double[] toArray() {
        return matrix;
    }

}
