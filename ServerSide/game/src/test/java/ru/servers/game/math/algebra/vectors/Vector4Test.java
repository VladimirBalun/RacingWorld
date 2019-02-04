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

package ru.servers.game.math.algebra.vectors;

import org.junit.Assert;
import org.junit.Test;

public class Vector4Test {

    @Test // vector = ( x1 + x2; y1 + y2; z1 + z2 )
    public void additionOfVectors() {
        Vector4 firstVector = new Vector4(5.0, 7.0, 4.0, 1.0);
        Vector4 secondVector = new Vector4(5.0, 3.0, 6.0, 1.0);
        firstVector.add(secondVector);
        Assert.assertEquals(new Vector4(10.0, 10.0, 10.0, 1.0), firstVector);
    }

    @Test // vector = ( x1 - x2; y1 - y2; z1 - z2 )
    public void subtractionOfVectors(){
        Vector4 firstVector = new Vector4(15.0, 17.0, 18.0, 1.0);
        Vector4 secondVector = new Vector4(5.0, 7.0, 8.0, 1.0);
        firstVector.sub(secondVector);
        Assert.assertEquals(new Vector4(10.0, 10.0, 10.0, 1.0), firstVector);
    }

    @Test // vector = ( x * scalar; y * scalar; z * scalar )
    public void multiplicationOfVectorsByScalar(){
        Vector4 vector = new Vector4(5.0, 5.0, 5.0, 1.0);
        vector.mul(2.0);
        Assert.assertEquals(new Vector4(10.0, 10.0, 10.0, 1.0), vector);
    }

    @Test // scalar = x1*x2 + y1*y2 + z1*z2
    public void dotProductOfVectors(){
        Vector4 vector = new Vector4(5.0, 5.0, 5.0, 1.0);
        double scalar = vector.dot(new Vector4(1.0, 1.0, 1.0, 1.0));
        Assert.assertEquals(15.0, scalar, 0.1);
    }

    @Test // vector = ( y1*z2 - z1*y2; -(x1*z2 - z1*x2); x1*y2 - y1*x2 )
    public void crossProductOfVector(){
        Vector4 vector = new Vector4(1.0, 2.0, 3.0, 1.0);
        Vector4 anotherVector = new Vector4(4.0, 5.0, 6.0, 1.0);
        vector.cross(anotherVector);
        Assert.assertEquals(new Vector4(-3.0, 6.0, -3.0, 1.0), vector);
    }

    @Test // vector = ( x / |x|; y / |y|; z / |z| )
    public void normalizationOfVector(){
        Vector4 vector = new Vector4(5.0, 9.0, 7.0, 1.0);
        vector.normalize();
        Assert.assertEquals(1.0, vector.getLength(), 0.1);
    }

}
