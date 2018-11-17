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
public class Vector2d {

    private double x;
    private double y;

    public void add(Vector2d anotherVector){
        this.x += anotherVector.x;
        this.y += anotherVector.y;
    }

    public void sub(Vector2d anotherVector){
        this.x -= anotherVector.x;
        this.y -= anotherVector.y;
    }

    public void mul(double scalar){
        this.x *= scalar;
        this.y *= scalar;
    }

    public double getLength(){
        return Math.sqrt((x*x) + (y*y));
    }

    public void normalize(){
        double lengthInversion = (1 / getLength());
        this.x *= lengthInversion;
        this.y *= lengthInversion;
    }

    public Vector3d toVector3d(){
        return new Vector3d(this.x, this.y, 0.0);
    }

    public Vector4d toVector4d(){
        return new Vector4d(this.x, this.y, 0.0, 0.0);
    }

    public double[] toArray(){
        return new double[] { this.x, this.y };
    }

}
