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

public class Vector3Test {

    @Test // (x + x, y + y, z + z)
    public void additionOfVectors() {
        Vector3 firstVector = new Vector3(5.0, 7.0, 4.0);
        Vector3 secondVector = new Vector3(5.0, 3.0, 6.0);
        firstVector.add(secondVector);
        Assert.assertEquals(new Vector3(10.0, 10.0, 10.0), firstVector);
    }

    @Test // (x - x, y - y, z - z)
    public void subtractionOfVectors9(){
        Vector3 firstVector = new Vector3(15.0, 17.0, 18.0);
        Vector3 secondVector = new Vector3(5.0, 7.0, 8.0);
        firstVector.sub(secondVector);
        Assert.assertEquals(new Vector3(10.0, 10.0, 10.0), firstVector);
    }

    @Test // (x * dot, y * dot, z * dot)
    public void multiplicationOfVectorsByScalar(){
        Vector3 vector = new Vector3(5.0, 5.0, 5.0);
        vector.mul(2.0);
        Assert.assertEquals(new Vector3(10.0, 10.0, 10.0), vector);
    }

    @Test // (x / |x|, y / |y|, z / |z|)
    public void normalizationOfVector(){
        Vector3 vector = new Vector3(5.0, 9.0, 7.0);
        vector.normalize();
        Assert.assertEquals(1.0, vector.getLength(), 0.1);
    }

}
