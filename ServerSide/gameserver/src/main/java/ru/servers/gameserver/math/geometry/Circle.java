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

import lombok.*;
import ru.servers.gameserver.math.algebra.vectors.Vector2;
import ru.servers.gameserver.math.algebra.vectors.Vectors;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Circle {

    private double radius;
    private Vector2 centerPoint;

    public double getDiameter(){
        return radius * 2;
    }

    public double getArea(){
        return Math.PI * radius * radius;
    }

    public double getLength(){
        return Math.PI * radius;
    }

    public boolean isInside(Vector2 point){
        double lengthBetweenPointAndCircleCenter = Vectors.getLengthBetweenTwoVectors(point, centerPoint);
        return lengthBetweenPointAndCircleCenter < radius;
    }

}
