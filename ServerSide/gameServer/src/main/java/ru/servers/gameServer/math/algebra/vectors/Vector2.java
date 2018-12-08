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

import lombok.*;
import ru.servers.gameServer.math.Point2;
import ru.servers.gameServer.math.Point3;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Vector2 {

    private double x;
    private double y;

    public void add(Vector2 anotherVector){
        x += anotherVector.x;
        y += anotherVector.y;
    }

    public void sub(Vector2 anotherVector){
        x -= anotherVector.x;
        y -= anotherVector.y;
    }

    public void mul(double scalar){
        x *= scalar;
        y *= scalar;
    }

    public double getLength(){
        return Math.sqrt((x*x) + (y*y));
    }

    public void normalize(){
        double length = getLength();
        if (length != 0) {
            x /= length;
            y /= length;
        }
    }

    public Vector3 toVector3(){
        return new Vector3(x, y, 0.0);
    }

    public Vector4 toVector4(){
        return new Vector4(x, y, 0.0, 0.0);
    }

    public Point2 toPoint2(){
        return new Point2(x, y);
    }

    public Point3 toPoint3(){
        return new Point3(x, y, 0.0);
    }

    public double[] toArray(){
        return new double[] { x, y };
    }

}
