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

import ru.servers.gameServer.math.Constants;

public class Vectors {

    public static double dot(Vector2 vector, Vector2 anotherVector){
        return vector.getX() * anotherVector.getX() +
               vector.getY() * anotherVector.getY();
    }

    public static double dot(Vector3 vector, Vector3 anotherVector){
        return vector.getX() * anotherVector.getX() +
               vector.getY() * anotherVector.getY() +
               vector.getZ() * anotherVector.getZ();
    }

    public static double getAngleBetweenVectors(Vector2 vector, Vector2 anotherVector){
        double scalar = dot(vector, anotherVector);
        double determinant = vector.getX()*anotherVector.getY() - vector.getY()*anotherVector.getX();
        return Math.atan2(determinant, scalar) * Constants.RADIANS_TO_DEGREES;
    }

    public static double getAngleBetweenVectors(Vector3 vector, Vector3 anotherVector){
        double scalar = dot(vector, anotherVector);
        double lenVectorWithoutSqrt = vector.getX() + vector.getY() + vector.getZ();
        double lenAnotherVectorWithoutSqrt = anotherVector.getX() + anotherVector.getY() + anotherVector.getZ();
        return Math.acos(scalar / Math.sqrt(lenVectorWithoutSqrt*lenAnotherVectorWithoutSqrt)) * Constants.RADIANS_TO_DEGREES;
    }

}
