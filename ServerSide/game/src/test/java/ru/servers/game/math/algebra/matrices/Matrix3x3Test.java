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

import org.junit.Assert;
import org.junit.Test;
import ru.servers.game.math.algebra.vectors.Vector3;

public class Matrix3x3Test {

    private double[] firstMatrix = {
            1.0, 2.0, 3.0,
            1.0, 2.0, 3.0,
            1.0, 2.0, 3.0
    };

    private double[] secondMatrix = {
            5.0, 5.0, 5.0,
            5.0, 5.0, 5.0,
            5.0, 5.0, 5.0
    };

    @Test // matrix = [ m1[0][0] + m2[0][0], ..., m1[2][2] + m2[2][2] ]
    public void additionMatrices(){
        Matrix3x3 matrix = new Matrix3x3(firstMatrix);
        matrix.add(new Matrix3x3(secondMatrix));
        Assert.assertArrayEquals(new double[]{
                6.0, 7.0, 8.0,
                6.0, 7.0, 8.0,
                6.0, 7.0, 8.0
        }, matrix.toArray(), 0.1);
    }

    @Test // matrix = [ m1[0][0] - m2[0][0], ..., m1[2][2] - m2[2][2] ]
    public void subtractionMatrices(){
        Matrix3x3 matrix = new Matrix3x3(secondMatrix);
        matrix.sub(new Matrix3x3(firstMatrix));
        Assert.assertArrayEquals(new double[]{
                4.0, 3.0, 2.0,
                4.0, 3.0, 2.0,
                4.0, 3.0, 2.0
        }, matrix.toArray(), 0.1);
    }

    @Test // matrix = [ m[0][0] * scalar, ..., m[2][2] * scalar ]
    public void multiplicationMatrixByScalar(){
        Matrix3x3 matrix = new Matrix3x3(secondMatrix);
        matrix.mul(2.0);
        Assert.assertArrayEquals(new double[]{
                10.0, 10.0, 10.0,
                10.0, 10.0, 10.0,
                10.0, 10.0, 10.0
        }, matrix.toArray(), 0.1);
    }

    @Test // vector = ( m[0][0]*vec.x + m[0][1]*vec.y + m[0][2]*vec.z; ... ; ... )
    public void multiplicationMatrixByVector(){
        Vector3 vector = new Vector3(1.0, 2.0, 3.0);
        Matrix3x3 matrix = new Matrix3x3(firstMatrix);
        Vector3 newVector = matrix.mul(vector);
        Assert.assertEquals(new Vector3(0.0, 0.0, 0.0), newVector);
    }

    @Test // matrix = [ m[0][0] = m[0][0], m[0][1] = m[1][0] ..., m[2][2] = m[2][2] ]
    public void transpositionMatrix(){
        Matrix3x3 matrix = new Matrix3x3(firstMatrix);
        matrix.transpose();
        Assert.assertArrayEquals(new double[]{
                1.0, 1.0, 1.0,
                2.0, 2.0, 2.0,
                3.0, 3.0, 3.0
        }, matrix.toArray(), 0.1);
    }

}
