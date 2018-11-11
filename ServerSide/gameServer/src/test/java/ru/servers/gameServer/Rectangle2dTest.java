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
import ru.servers.gameServer.math.geometry.Rectangle2d;

public class Rectangle2dTest {

    private Rectangle2d rectangle = new Rectangle2d(
            new Vector2d(0.0, 0.0), // (0;5)      (5;5)
            new Vector2d(0.0, 5.0), //
            new Vector2d(5.0, 5.0), //
            new Vector2d(5.0, 0.0)  // (0;0)      (5;0)
    );

    @Test
    public void gettingAreaOfRectangle(){
        // a*b
        Assert.assertEquals(25.0, rectangle.getArea(), 0.1);
    }

    @Test
    public void gettingPerimeterOfRectangle(){
        // 2(a*b)
        Assert.assertEquals(20.0, rectangle.getPerimeter(), 0.1);
    }

    @Test
    public void gettingDiagonalLengthOfRectangle(){
        // Sqrt(a*b + a*b)
        Assert.assertEquals(7.0, rectangle.getDiagonalLength(), 0.9);
    }

    @Test
    public void gettingLengthOfRectangle(){
        // Sqrt(((a-b)^2) + ((a-b)^2))
        Assert.assertEquals(5.0, rectangle.getLength(), 0.1);
    }

    @Test
    public void gettingWidthOfRectangle(){
        // Sqrt(((a-b)^2) + ((a-b)^2))
        Assert.assertEquals(5.0, rectangle.getWidth(), 0.1);
    }

}
