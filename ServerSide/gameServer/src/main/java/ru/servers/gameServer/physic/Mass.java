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

package ru.servers.gameServer.physic;

import ru.servers.gameServer.math.Point2;

public class Mass {

    public static Point2 getMassCenter(Point2... points) throws IllegalArgumentException {
        int count_vertexes = points.length;
        if (count_vertexes == 0) {
            throw new IllegalArgumentException("Count points is null.");
        }

        Point2 massCenter = new Point2();
        for (Point2 point : points) {
            massCenter.setX(massCenter.getX() + point.getX());
            massCenter.setY(massCenter.getY() + point.getY());
        }

        massCenter.setX(massCenter.getX() / count_vertexes);
        massCenter.setY(massCenter.getY() / count_vertexes);
        return massCenter;
    }

}
