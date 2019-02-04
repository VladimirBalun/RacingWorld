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

package ru.servers.game.math.algebra.vectors;

import lombok.*;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Vector4 {

    private double x;
    private double y;
    private double z;
    private double w;

    public void add(Vector4 another){
        x += another.x;
        y += another.y;
        z += another.z;
    }

    public void sub(Vector4 another){
        x -= another.x;
        y -= another.y;
        z -= another.z;
    }

    public void mul(double scalar){
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    public double dot(Vector4 another){
        return x*another.getX() + y*another.getY() + z*another.getZ();
    }

    public void cross(Vector4 another){
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
        double length =  getLength();
        if (length != 0) {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    public Vector2 toVector2(){
        return new Vector2(x, y);
    }

    public Vector3 toVector3(){
        return new Vector3(x, y, z);
    }

    public double[] toArray(){
        return new double[] { x, y, z, w };
    }

}
