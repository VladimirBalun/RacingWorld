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

package ru.servers.gameserver.math.geometry;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameserver.math.algebra.vectors.Vector2;

public class TriangleTest {

    private Triangle triangle = new Triangle(
            new Vector2(0.0, 0.0), //       (5;5)
            new Vector2(5.0, 5.0), //
            new Vector2(10.0, 0.0)  // (0;0)     (10;0)
    );

    @Test  // Sqrt(p(p-a) * (p-b) * (p-c))
    public void gettingAreaOfTriangle(){
        double firstSide = Math.sqrt(Math.pow((0.0 - 5.0), 2) + Math.pow((0.0 - 5.0), 2));
        double secondSide = Math.sqrt(Math.pow((5.0 - 10.0), 2) + Math.pow((5.0 - 0.0), 2));
        double thirdSide = Math.sqrt(Math.pow((10.0 - 0.0), 2) + Math.pow((0.0 - 0.0), 2));
        double perimeter = firstSide + secondSide + thirdSide;
        double area = Math.sqrt(perimeter * (perimeter-firstSide) * (perimeter-secondSide) * (perimeter-thirdSide));
        Assert.assertEquals(area, triangle.getArea(), 0.1);
    }

    @Test  // a + b + c
    public void gettingPerimeterOfTriangle(){
        double firstSide = Math.sqrt(Math.pow((0.0 - 5.0), 2) + Math.pow((0.0 - 5.0), 2));
        double secondSide = Math.sqrt(Math.pow((5.0 - 10.0), 2) + Math.pow((5.0 - 0.0), 2));
        double thirdSide = Math.sqrt(Math.pow((10.0 - 0.0), 2) + Math.pow((0.0 - 0.0), 2));
        double perimeter = firstSide + secondSide + thirdSide;
        Assert.assertEquals(perimeter, triangle.getPerimeter(), 0.1);
    }

    @Test  // Test1: Check vertex x in Triangle
    public void checkingVertexOnNonExistingInTriange(){
        Vector2 vertex = new Vector2(7.78,2.38);
        Assert.assertEquals(false, triangle.isInside(vertex));
    }

    @Test  // Test2: Check vertex x in Triangle
    public void checkingVertexOnExistingOnTriangeBorder(){
        Vector2 vertex = new Vector2(0.0001,0);
        Assert.assertEquals(true, triangle.isInside(vertex));
    }

    @Test  // Test3: Check vertex x in Triangle
    public void checkingVertexOnExistingInTriange(){
        Triangle triangle = new Triangle(
                new Vector2(4.6, -1.02),  //              (6,3;4,38)
                new Vector2(6.3, 4.38),   //                          (12,14;2,58)
                new Vector2(12.14, 2.58)  // (4,6;-1,2)
        );
        Vector2 vertex = new Vector2(7.38,2.38);
        Assert.assertEquals(true, triangle.isInside(vertex));
    }

}
