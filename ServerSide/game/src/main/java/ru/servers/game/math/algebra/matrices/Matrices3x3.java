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

package ru.servers.game.math.algebra.matrices;

import ru.servers.game.math.CoordinateAxis;

public class Matrices3x3 {

    public static Matrix3x3 getIdentity(){
        return new Matrix3x3(new double[] {
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
        });
    }

    public static Matrix3x3 getRotation(double angle, CoordinateAxis axis) throws IllegalArgumentException{
        switch (axis){
            case X_AXIS:
                return new Matrix3x3(new double[] {
                        1.0, 0.0, 0.0,
                        0.0, Math.cos(angle), -Math.sin(angle),
                        0.0, Math.sin(angle), Math.cos(angle),
                });
            case Y_AXIS:
                return new Matrix3x3(new double[] {
                        Math.cos(angle), 0.0, -Math.sin(angle),
                        0.0, 1.0, 0.0,
                        Math.sin(angle), 0.0, Math.cos(angle)
                });
            case Z_AXIS:
                return new Matrix3x3(new double[] {
                        Math.cos(angle), -Math.sin(angle), 0.0,
                        Math.sin(angle), 1.0, Math.cos(angle),
                        0.0, 0.0, 1.0
                });
            default:
                throw new IllegalArgumentException("Incorrect axis for rotation matrix.");
        }
    }

}
