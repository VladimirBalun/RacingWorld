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

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Vector3d {

    private double x;
    private double y;
    private double z;

    public void add(Vector3d anotherVector){
        this.x += anotherVector.x;
        this.y += anotherVector.y;
        this.z += anotherVector.z;
    }

    public void sub(Vector3d anotherVector){
        this.x -= anotherVector.x;
        this.y -= anotherVector.y;
        this.z -= anotherVector.z;
    }

    public void mul(double scalar){
        this.x *= scalar;
        this.y *= scalar;
        this.z *= scalar;
    }

    public double getLength(){
        return Math.sqrt((x*x) + (y*y) + (z*z));
    }

    public void normalize(){
        double length =  this.getLength();
        if (length != 0) {
            this.x /= length;
            this.y /= length;
            this.z /= length;
        }
    }

    public Vector2d toVector2d(){
        return new Vector2d(this.x, this.y);
    }

    public Vector4d toVector4d(){
        return new Vector4d(this.x, this.y, 0.0, 0.0);
    }

    public double[] toArray(){
        return new double[] { this.x, this.y, this.z };
    }

}
