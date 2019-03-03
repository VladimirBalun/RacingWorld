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

import lombok.*;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Vector3 {

    private double x;
    private double y;
    private double z;

    public void add(Vector3 another){
        x += another.x;
        y += another.y;
        z += another.z;
    }

    public void sub(Vector3 another){
        x -= another.x;
        y -= another.y;
        z -= another.z;
    }

    public void mul(double scalar){
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    public double dot(Vector3 another){
        return x*another.getX() + y*another.getY() + z*another.getZ();
    }

    public void cross(Vector3 another){
        double tmpX = y*another.z - z*another.y;
        double tmpY = -(x*another.z - z*another.x);
        double tmpZ = x*another.y - y*another.x;
        x = tmpX;
        y = tmpY;
        z = tmpZ;
    }

    public double getLength(){
        return Math.sqrt((x*x) + (y*y) + (z*z));
    }

    public void normalize(){
        double length = getLength();
        if (length != 0) {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    public Vector2 toVector2(){
        return new Vector2(x, y);
    }

    public Vector4 toVector4(){
        return new Vector4(x, y, 0.0, 1.0);
    }

    public double[] toArray(){
        return new double[] { x, y, z };
    }

}
