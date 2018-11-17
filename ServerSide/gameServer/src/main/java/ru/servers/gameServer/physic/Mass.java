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

import ru.servers.gameServer.math.algebra.vectors.Vector2d;

public class Mass {

    public static Vector2d getMassCenter(Vector2d ...vertexes) throws IllegalArgumentException {
        int count_vertexes = vertexes.length;
        if (count_vertexes == 0) {
            throw new IllegalArgumentException("Count vertexes is null.");
        }

        Vector2d massCenter = new Vector2d();
        for (Vector2d vertex : vertexes) {
            massCenter.setX(massCenter.getX() + vertex.getX());
            massCenter.setY(massCenter.getY() + vertex.getY());
        }

        massCenter.setX(massCenter.getX() / count_vertexes);
        massCenter.setY(massCenter.getY() / count_vertexes);
        return massCenter;
    }

}
