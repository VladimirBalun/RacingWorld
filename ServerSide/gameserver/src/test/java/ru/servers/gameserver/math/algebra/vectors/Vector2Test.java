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

package ru.servers.gameserver.math.algebra.vectors;

import org.junit.Assert;
import org.junit.Test;

public class Vector2Test {

    @Test // vector = ( x1 + x2; y1 + y2 )
    public void additionOfVectors() {
        Vector2 firstVector = new Vector2(5.0, 7.0);
        Vector2 secondVector = new Vector2(5.0, 3.0);
        firstVector.add(secondVector);
        Assert.assertEquals(new Vector2(10.0, 10.0), firstVector);
    }

    @Test // vector = ( x1 - x2; y1 - y2 )
    public void subtractionOfVectors(){
        Vector2 firstVector = new Vector2(15.0, 17.0);
        Vector2 secondVector = new Vector2(5.0, 7.0);
        firstVector.sub(secondVector);
        Assert.assertEquals(new Vector2(10.0, 10.0), firstVector);
    }

    @Test // vector = ( x * scalar; y * scalar )
    public void multiplicationOfVectorsByScalar(){
        Vector2 vector = new Vector2(5.0, 5.0);
        vector.mul(2.0);
        Assert.assertEquals(new Vector2(10.0, 10.0), vector);
    }

    @Test // scalar = x1*x2 + y1*y2
    public void dotProductOfVectors(){
        Vector2 vector = new Vector2(5.0, 5.0);
        double scalar = vector.dot(new Vector2(1.0, 1.0));
        Assert.assertEquals(10.0, scalar, 0.1);
    }

    @Test // vector = ( x / |x|; y / |y| )
    public void normalizationOfVector(){
        Vector2 vector = new Vector2(5.0, 9.0);
        vector.normalize();
        Assert.assertEquals(1.0, vector.getLength(), 0.1);
    }

}
