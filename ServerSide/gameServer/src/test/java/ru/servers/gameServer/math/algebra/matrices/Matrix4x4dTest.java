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

import org.junit.Assert;
import org.junit.Test;

public class Matrix4x4dTest {

    private double[] firstMatrix = {
            1.0, 2.0, 3.0, 4.0,
            1.0, 2.0, 3.0, 4.0,
            1.0, 2.0, 3.0, 4.0,
            1.0, 2.0, 3.0, 4.0
    };

    private double[] secondMatrix = {
            5.0, 5.0, 5.0, 5.0,
            5.0, 5.0, 5.0, 5.0,
            5.0, 5.0, 5.0, 5.0,
            5.0, 5.0, 5.0, 5.0
    };

    @Test // m[0] + n[0], ..., m[15] + n[15]
    public void additionMatrices(){
        Matrix4x4d matrix = new Matrix4x4d(firstMatrix);
        matrix.add(new Matrix4x4d(secondMatrix));
        Assert.assertArrayEquals(new double[]{
                6.0, 7.0, 8.0, 9.0,
                6.0, 7.0, 8.0, 9.0,
                6.0, 7.0, 8.0, 9.0,
                6.0, 7.0, 8.0, 9.0
        }, matrix.toArray(), 0.1);
    }

    @Test // m[0] - n[0], ..., m[15] - n[15]
    public void subtractionMatrices(){
        Matrix4x4d matrix = new Matrix4x4d(secondMatrix);
        matrix.sub(new Matrix4x4d(firstMatrix));
        Assert.assertArrayEquals(new double[]{
                4.0, 3.0, 2.0, 1.0,
                4.0, 3.0, 2.0, 1.0,
                4.0, 3.0, 2.0, 1.0,
                4.0, 3.0, 2.0, 1.0
        }, matrix.toArray(), 0.1);
    }

    @Test // m[0] * scalar, ..., m[15] * scalar
    public void multiplicationMatrixByScalar(){
        Matrix4x4d matrix = new Matrix4x4d(secondMatrix);
        matrix.mul(2);
        Assert.assertArrayEquals(new double[]{
                10.0, 10.0, 10.0, 10.0,
                10.0, 10.0, 10.0, 10.0,
                10.0, 10.0, 10.0, 10.0,
                10.0, 10.0, 10.0, 10.0
        }, matrix.toArray(), 0.1);
    }

    @Test // m[0] = m[0], m[1] = m[4] ..., m[15] = m[15]
    public void transpositionMatrices(){
        Matrix4x4d matrix = new Matrix4x4d(firstMatrix);
        matrix.transpose();
        Assert.assertArrayEquals(new double[]{
                1.0, 1.0, 1.0, 1.0,
                2.0, 2.0, 2.0, 2.0,
                3.0, 3.0, 3.0, 3.0,
                4.0, 4.0, 4.0, 4.0
        }, matrix.toArray(), 0.1);
    }

}
