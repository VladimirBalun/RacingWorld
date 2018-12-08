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

package ru.servers.gameServer.math.geometry;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.math.Point2;

public class CircleTest {

    //   _____
    //  /     \
    // | (5;5) |
    //  \_____/
    private final double radius = 5.0;
    private final Point2 centerPoint = new Point2(5.0, 5.0);
    private Circle circle = new Circle(radius, centerPoint);

    @Test // PI * r^2
    public void gettingAreaOfCircle(){
        double area = Math.PI * radius * radius;
        Assert.assertEquals(area, circle.getArea(), 0.1);
    }

    @Test // PI * r
    public void gettingLengthOfCircle(){
        double length = Math.PI * radius;
        Assert.assertEquals(length, circle.getLength(), 0.1);
    }

    @Test // r * 2
    public void gettingDiameter(){
        double diameter = radius * 2;
        Assert.assertEquals(diameter, circle.getDiameter(), 0.1);
    }

    @Test
    public void checkingIfPointIsInsideRectangle(){
        Assert.assertTrue(circle.isInside(new Point2(2.5, 2.5)));
    }

}
