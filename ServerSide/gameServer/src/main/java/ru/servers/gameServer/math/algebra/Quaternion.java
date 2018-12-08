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

package ru.servers.gameServer.math.algebra;

import lombok.*;
import ru.servers.gameServer.math.algebra.vectors.Vector3;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Quaternion {

    private double w;
    private Vector3 vector;

    public void add(Quaternion quaternion){
        w += quaternion.w;
        vector.setX(vector.getX() + quaternion.vector.getX());
        vector.setY(vector.getY() + quaternion.vector.getY());
        vector.setZ(vector.getZ() + quaternion.vector.getZ());
    }

    public void sub(Quaternion quaternion){
        w -= quaternion.w;
        vector.setX(vector.getX() - quaternion.vector.getX());
        vector.setY(vector.getY() - quaternion.vector.getY());
        vector.setZ(vector.getZ() - quaternion.vector.getZ());
    }

    public void mul(double scalar){
        w *= scalar;
        vector.setX(vector.getX() * scalar);
        vector.setY(vector.getY() * scalar);
        vector.setZ(vector.getZ() * scalar);
    }

}
