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

package ru.servers.gameServer.math.algebra.vectors;

import org.junit.Assert;
import org.junit.Test;

public class VectorsTest {

    @Test // x*x + y*y
    public void scalarMultiplicationOfVectors2d(){
        double scalar = Vectors.scalar(new Vector2d(5.0, 5.0), new Vector2d(1.0, 1.0));
        Assert.assertEquals(10.0, scalar, 0.1);
    }

    @Test // x*x + y*y + z*z
    public void scalarMultiplicationOfVectors3d(){
        double scalar = Vectors.scalar(new Vector3d(5.0, 5.0, 5.0), new Vector3d(1.0, 1.0, 1.0));
        Assert.assertEquals(15.0, scalar, 0.1);
    }

    @Test // atan(v1 * v2, det(v1 && v2)) * 57.29
    public void gettingAngleBetweenVectors2d(){
        double angle = Vectors.getAngleBetweenVectors(new Vector2d(1.0, 1.0), new Vector2d(0.0, 1.0));
        Assert.assertEquals(45.0, angle, 0.1);
    }

    @Test // acos(v1 * v2 / (|v1| * |v2|)) * 57.29
    public void gettingAngleBetweenVectors3d(){
        double angle = Vectors.getAngleBetweenVectors(new Vector3d(1.0, 1.0, 1.0), new Vector3d(0.5, 0.5, 0.5));
        Assert.assertEquals(45.0, angle, 0.1);
    }

    @Test // (v1(x) == v2(x), v1(y) == v2(y))
    public void equalityOfVectors2d(){
        boolean result = Vectors.isEquals(new Vector2d(5.0, 5.0), new Vector2d(5.0, 5.0));
        Assert.assertTrue(result);
    }

    @Test // (v1(x) == v2(x), v1(y) == v2(y), v1(z) == v2(z))
    public void equalityOfVectors3d(){
        boolean result = Vectors.isEquals(new Vector3d(5.0, 5.0, 5.0), new Vector3d(5.0, 5.0, 5.0));
        Assert.assertTrue(result);
    }

}
