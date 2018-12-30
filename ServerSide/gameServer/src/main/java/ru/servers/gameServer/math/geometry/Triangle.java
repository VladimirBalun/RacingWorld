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

import lombok.*;
import ru.servers.gameServer.math.algebra.vectors.Vector2;
import ru.servers.gameServer.math.algebra.vectors.Vectors;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Triangle {

    private Vector2 firstPoint;
    private Vector2 secondPoint;
    private Vector2 thirdPoint;

    public double getPerimeter(){
        double firstSide = Vectors.getLengthBetweenTwoVectors(firstPoint, secondPoint);
        double secondSide = Vectors.getLengthBetweenTwoVectors(secondPoint, thirdPoint);
        double thirdSide = Vectors.getLengthBetweenTwoVectors(thirdPoint, firstPoint);
        return firstSide + secondSide + thirdSide;
    }

    public double getArea(){
        double perimeter = getPerimeter();
        double firstSide = Vectors.getLengthBetweenTwoVectors(firstPoint, secondPoint);
        double secondSide = Vectors.getLengthBetweenTwoVectors(secondPoint, thirdPoint);
        double thirdSide = Vectors.getLengthBetweenTwoVectors(thirdPoint, firstPoint);
        return Math.sqrt(perimeter * (perimeter-firstSide) * (perimeter-secondSide) * (perimeter-thirdSide));
    }

}
