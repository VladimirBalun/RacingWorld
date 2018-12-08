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
import ru.servers.gameServer.math.Points;
import ru.servers.gameServer.math.Point2;

@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Rectangle {

    private Point2 leftBottomPoint;
    private Point2 leftTopPoint;
    private Point2 rightTopPoint;
    private Point2 rightBottomPoint;

    public double getArea(){
        double length = getLength();
        double width = getWidth();
        return length * width;
    }

    public double getPerimeter(){
        return 2 * (getWidth() + getLength());
    }

    public double getLength(){
        double firstDifference = Points.getLengthBetweenTwoPoints(leftTopPoint, rightTopPoint);
        double secondDifference = Points.getLengthBetweenTwoPoints(leftTopPoint, leftBottomPoint);
        return firstDifference > secondDifference ? firstDifference : secondDifference;
    }

    public double getDiagonalLength(){
        return Math.sqrt(getLength()*getLength() + getWidth()*getWidth());
    }

    public double getWidth(){
        double firstDifference = Points.getLengthBetweenTwoPoints(leftTopPoint, rightTopPoint);
        double secondDifference = Points.getLengthBetweenTwoPoints(leftTopPoint, leftBottomPoint);
        return firstDifference < secondDifference ? firstDifference : secondDifference;
    }

    public boolean isInside(Point2 point) {

        return (leftBottomPoint.getX() < point.getX() && point.getX() < rightBottomPoint.getX()) &&
               (leftBottomPoint.getY() < point.getY() && point.getY() < leftTopPoint.getY());
    }

    public Point2[] toPointArray(){
        return new Point2[] {
                this.leftBottomPoint,
                this.leftTopPoint,
                this.rightTopPoint,
                this.rightBottomPoint
        };
    }

}
