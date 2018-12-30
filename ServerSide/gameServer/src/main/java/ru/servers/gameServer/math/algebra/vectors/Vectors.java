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

    public static double getAngleBetweenVectors(Vector2 vector, Vector2 anotherVector){
        double scalar = vector.dot(anotherVector);
        double determinant = vector.getX()*anotherVector.getY() - vector.getY()*anotherVector.getX();
        return Math.atan2(determinant, scalar) * Constants.RADIANS_TO_DEGREES;
    }

    public static double getAngleBetweenVectors(Vector3 vector, Vector3 anotherVector){
        double scalar = vector.dot(anotherVector);
        double lenVectorWithoutSqrt = vector.getX() + vector.getY() + vector.getZ();
        double lenAnotherVectorWithoutSqrt = anotherVector.getX() + anotherVector.getY() + anotherVector.getZ();
        return Math.acos(scalar / Math.sqrt(lenVectorWithoutSqrt*lenAnotherVectorWithoutSqrt)) * Constants.RADIANS_TO_DEGREES;
    }

    public static double getLengthBetweenTwoVectors(Vector2 vector, Vector2 anotherVector){
        double absDifferenceX = vector.getX() - anotherVector.getX();
        double absDifferenceY = vector.getY() - anotherVector.getY();
        return Math.sqrt(absDifferenceX*absDifferenceX + absDifferenceY*absDifferenceY);
    }

    public static double getLengthBetweenTwoVectors(Vector3 point, Vector3 anotherVector){
        double absDifferenceX = point.getX() - anotherVector.getX();
        double absDifferenceY = point.getY() - anotherVector.getY();
        double absDifferenceZ = point.getZ() - anotherVector.getZ();
        return Math.sqrt(absDifferenceX*absDifferenceX +
                absDifferenceY*absDifferenceY +
                absDifferenceZ*absDifferenceZ);
    }

}
