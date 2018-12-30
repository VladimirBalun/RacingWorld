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

package ru.servers.gameServer.physic;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.math.algebra.vectors.Vector2;
import ru.servers.gameServer.math.geometry.Rectangle;

public class MassTest {

    @Test // (x+x[1]+x[2]+x[3]+x[4]) / 4, (y + ...) / 4
    public void gettingCenterOfMassOfRectangle(){
        Rectangle rectangle = new Rectangle(
                new Vector2(2.0, 2.0), // (2;4)      (4;4)
                new Vector2(2.0, 4.0), //
                new Vector2(4.0, 4.0), //
                new Vector2(4.0, 2.0)  // (2;2)      (4;2)
        );
        Vector2 massCenter = Mass.getMassCenter(rectangle.toVectorArray());
        Assert.assertEquals(new Vector2(3.0, 3.0), massCenter);
    }

    @Test (expected = IllegalArgumentException.class)
    public void gettingCenterOfMassWithNullCountVertexes(){
        Mass.getMassCenter();
    }

}
