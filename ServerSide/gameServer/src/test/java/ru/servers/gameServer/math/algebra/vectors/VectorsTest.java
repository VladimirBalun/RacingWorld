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

    @Test // angle = atan(v1 * v2, det(v1 && v2)) * 57.29
    public void gettingAngleBetweenVectors2d(){
        double angle = Vectors.getAngleBetweenVectors(new Vector2(1.0, 1.0), new Vector2(0.0, 1.0));
        Assert.assertEquals(45.0, angle, 0.1);
    }

    @Test // angle = acos(v1 * v2 / (|v1| * |v2|)) * 57.29
    public void gettingAngleBetweenVectors3d(){
        double angle = Vectors.getAngleBetweenVectors(new Vector3(1.0, 1.0, 1.0), new Vector3(0.5, 0.5, 0.5));
        Assert.assertEquals(45.0, angle, 0.1);
    }

    @Test // ( x1 == x2; y1 == y2 )
    public void equalityOfVectors2d(){
        boolean result = new Vector2(5.0, 5.0).equals(new Vector2(5.0, 5.0));
        Assert.assertTrue(result);
    }

    @Test // ( x1 == x2; y1 == y2; z1 == z2 )
    public void equalityOfVectors3d(){
        boolean result = new Vector3(5.0, 5.0, 5.0).equals(new Vector3(5.0, 5.0, 5.0));
        Assert.assertTrue(result);
    }

    @Test // ( x1 == x2; y1 == y2; z1 == z2, w1 == w2 )
    public void equalityOfVectors4d(){
        boolean result = new Vector4(5.0, 5.0, 5.0, 1.0).equals(new Vector4(5.0, 5.0, 5.0, 1.0));
        Assert.assertTrue(result);
    }

}
