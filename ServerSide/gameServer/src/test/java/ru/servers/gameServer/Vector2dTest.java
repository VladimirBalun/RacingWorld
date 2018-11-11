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

package ru.servers.gameServer;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.math.algebra.Vector2d;

public class Vector2dTest {

    @Test
    public void additionOfVectors() {
        Vector2d firstVector = new Vector2d(5.0, 7.0);
        Vector2d secondVector = new Vector2d(5.0, 3.0);
        firstVector.add(secondVector);
        Assert.assertEquals(firstVector, new Vector2d(10.0, 10.0));
    }

    @Test
    public void subtractionOfVectors9(){
        Vector2d firstVector = new Vector2d(15.0, 17.0);
        Vector2d secondVector = new Vector2d(5.0, 7.0);
        firstVector.sub(secondVector);
        Assert.assertEquals(firstVector, new Vector2d(10.0, 10.0));
    }

    @Test
    public void multiplicationOfVectorsByScalar(){
        Vector2d vector = new Vector2d(5.0, 5.0);
        vector.mulOnScalar(2.0);
        Assert.assertEquals(vector, new Vector2d(10.0, 10.0));
    }

    @Test
    public void normalizationOfVector(){
        Vector2d vector = new Vector2d(5.0, 9.0);
        vector.normalize();
        System.out.println(vector.getLength());
        Assert.assertEquals(1.0, vector.getLength(), 0.1);
    }

}
