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

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameserver.math.algebra.vectors.Vector4;

public class Matrix4x4Test {

    private final double[] firstMatrix = {
            1.0, 2.0, 3.0, 4.0,
            1.0, 2.0, 3.0, 4.0,
            1.0, 2.0, 3.0, 4.0,
            1.0, 2.0, 3.0, 4.0
    };

    private final double[] secondMatrix = {
            5.0, 5.0, 5.0, 5.0,
            5.0, 5.0, 5.0, 5.0,
            5.0, 5.0, 5.0, 5.0,
            5.0, 5.0, 5.0, 5.0
    };

    @Test // matrix = [ m1[0][0] + m2[0][0], ..., m1[3][3] + m2[3][3] ]
    public void additionMatrices(){
        Matrix4x4 matrix = new Matrix4x4(firstMatrix);
        matrix.add(new Matrix4x4(secondMatrix));
        Assert.assertArrayEquals(new double[]{
                6.0, 7.0, 8.0, 9.0,
                6.0, 7.0, 8.0, 9.0,
                6.0, 7.0, 8.0, 9.0,
                6.0, 7.0, 8.0, 9.0
        }, matrix.toArray(), 0.1);
    }

    @Test // matrix = [ m1[0][0] - m2[0][0], ..., m1[3][3] - m2[3][3] ]
    public void subtractionMatrices(){
        Matrix4x4 matrix = new Matrix4x4(secondMatrix);
        matrix.sub(new Matrix4x4(firstMatrix));
        Assert.assertArrayEquals(new double[]{
                4.0, 3.0, 2.0, 1.0,
                4.0, 3.0, 2.0, 1.0,
                4.0, 3.0, 2.0, 1.0,
                4.0, 3.0, 2.0, 1.0
        }, matrix.toArray(), 0.1);
    }

    @Test // matrix = [ m[0][0] * scalar, ..., m[3][3] * scalar
    public void multiplicationMatrixByScalar(){
        Matrix4x4 matrix = new Matrix4x4(secondMatrix);
        matrix.mul(2.0);
        Assert.assertArrayEquals(new double[]{
                10.0, 10.0, 10.0, 10.0,
                10.0, 10.0, 10.0, 10.0,
                10.0, 10.0, 10.0, 10.0,
                10.0, 10.0, 10.0, 10.0
        }, matrix.toArray(), 0.1);
    }

    @Test // matrix [ m1[0][0] * m2[0][0] + m1[0][1] * m2[1][1], ... ]
    public void multiplicationMatrixByMatrix(){
        Matrix4x4 matrix = new Matrix4x4(firstMatrix);
        matrix.mul(new Matrix4x4(secondMatrix));
        Assert.assertArrayEquals(new double[]{
                50.0, 50.0, 50.0, 50.0,
                50.0, 50.0, 50.0, 50.0,
                50.0, 50.0, 50.0, 50.0,
                50.0, 50.0, 50.0, 50.0
        }, matrix.toArray(), 0.1);
    }

    @Test // vector = ( m[0][0]*vec.x + m[0][1]*vec.y + m[0][2]*vec.z; ... ; ... )
    public void multiplicationMatrixByVector(){
        Vector4 vector = new Vector4(1.0, 2.0, 3.0, 1.0);
        Matrix4x4 matrix = new Matrix4x4(firstMatrix);
        Vector4 newVector = matrix.mul(vector);
        Assert.assertEquals(new Vector4(14.0, 14.0, 14.0, 1.0), newVector);
    }

    @Test // matrix = [ m[0][0] = m[0][0], m[0][1] = m[1][0] ..., m[3][3] = m[3][3] ]
    public void transpositionMatrix(){
        Matrix4x4 matrix = new Matrix4x4(firstMatrix);
        matrix.transpose();
        Assert.assertArrayEquals(new double[]{
                1.0, 1.0, 1.0, 1.0,
                2.0, 2.0, 2.0, 2.0,
                3.0, 3.0, 3.0, 3.0,
                4.0, 4.0, 4.0, 4.0
        }, matrix.toArray(), 0.1);
    }

}
