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

package ru.servers.gameserver.math.algebra;

import lombok.*;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Quaternion {

    private double w;
    private Vector3 vector;

    public void add(Quaternion another){
        w += another.w;
        vector.setX(vector.getX() + another.vector.getX());
        vector.setY(vector.getY() + another.vector.getY());
        vector.setZ(vector.getZ() + another.vector.getZ());
    }

    public void sub(Quaternion another){
        w -= another.w;
        vector.setX(vector.getX() - another.vector.getX());
        vector.setY(vector.getY() - another.vector.getY());
        vector.setZ(vector.getZ() - another.vector.getZ());
    }

    public void mul(double scalar){
        w *= scalar;
        vector.setX(vector.getX() * scalar);
        vector.setY(vector.getY() * scalar);
        vector.setZ(vector.getZ() * scalar);
    }

    public void mul(Quaternion another){
        Vector3 anotherVector = another.vector;
        w = w*another.getW() - vector.getX()*anotherVector.getX() - vector.getY()*anotherVector.getY() - vector.getZ()*anotherVector.getZ();
        vector.setX(w*another.w + another.w*vector.getX() + vector.getY()*anotherVector.getZ() - anotherVector.getY()*vector.getZ());
        vector.setY(w*anotherVector.getY() + another.w*vector.getY() + vector.getZ()*anotherVector.getX() - anotherVector.getZ()*vector.getX());
        vector.setZ(w*anotherVector.getZ() + another.w*vector.getZ() + vector.getX()*anotherVector.getY() - anotherVector.getX()*vector.getY());
    }

}
