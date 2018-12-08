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

package ru.servers.gameServer.math.algebra;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.math.algebra.vectors.Vector3;

public class QuaternionTest {

    // Q = 5.0 + 1.0i + 2.0j + 3.0k
    private Quaternion quaternion = new Quaternion(5.0, new Vector3(1.0, 2.0, 3.0));

    @Test // w + w; xi + xi; yj + yj; zk + zk
    public void additionOfQuaternions(){
        quaternion.add(new Quaternion(5.0, new Vector3(2.0, 1.0, 0.0)));
        Assert.assertEquals(new Quaternion(10.0, new Vector3(3.0, 3.0, 3.0)), quaternion);
    }

    @Test // w - w; xi - xi; yj - yj; zk - zk
    public void subtractionOfQuaternions(){
        quaternion.sub(new Quaternion(5.0, new Vector3(1.0, 2.0, 3.0)));
        Assert.assertEquals(new Quaternion(0.0, new Vector3(0.0, 0.0, 0.0)), quaternion);
    }

    @Test // w * scalar; xi * scalar; yj * scalar; zk * scalar
    public void multiplicationOfQuaternionsByScalar(){
        quaternion.mul(2.0);
        Assert.assertEquals(new Quaternion(10.0, new Vector3(2.0, 4.0, 6.0)), quaternion);
    }


}
