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

package ru.servers.gameServer.math.algebra.matrices;

import ru.servers.gameServer.math.CoordinateAxis;
import ru.servers.gameServer.math.algebra.vectors.Vector3;

public class Matrices4x4 {

    public static Matrix4x4 getIdentity(){
        return new Matrix4x4(new double[] {
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
        });
    }

    public static Matrix4x4 getOrtho(double left, double right, double bottom, double top, double near, double far){
        return new Matrix4x4(new double[] {
                2 / (right-left), 0.0, 0.0, - (right+left) / (right-left),
                0.0, 2 / (top-bottom), 0.0, (top+bottom) / (top-bottom),
                0.0, 0.0, 2 / (far-near), - (far+near) / (far-near),
                0.0, 0.0, 0.0, 0.0
        });
    }

    public static Matrix4x4 getTranslation(Vector3 vector){
        return new Matrix4x4(new double[] {
                1.0, 0.0, 0.0, vector.getX(),
                0.0, 1.0, 0.0, vector.getY(),
                0.0, 0.0, 1.0, vector.getZ(),
                0.0, 0.0, 0.0, 1.0
        });
    }

    public static Matrix4x4 getScale(Vector3 vector){
        return new Matrix4x4(new double[] {
                vector.getX(), 0.0, 0.0, 0.0,
                0.0, vector.getY(), 0.0, 0.0,
                0.0, 0.0, vector.getZ(), 0.0,
                0.0, 0.0, 0.0, 1.0
        });
    }

    public static Matrix4x4 getRotation(double angle, CoordinateAxis axis) throws IllegalArgumentException{
        switch (axis){
            case X_AXIS:
                return new Matrix4x4(new double[] {
                        1.0, 0.0, 0.0, 0.0,
                        0.0, Math.cos(angle), -Math.sin(angle), 0.0,
                        0.0, Math.sin(angle), Math.cos(angle), 0.0,
                        0.0, 0.0, 0.0, 1.0
                });
            case Y_AXIS:
                return new Matrix4x4(new double[] {
                        Math.cos(angle), 0.0, -Math.sin(angle), 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        Math.sin(angle), 0.0, Math.cos(angle), 0.0,
                        0.0, 0.0, 0.0, 1.0
                });
            case Z_AXIS:
                return new Matrix4x4(new double[] {
                        Math.cos(angle), -Math.sin(angle), 0.0, 0.0,
                        Math.sin(angle), 1.0, Math.cos(angle), 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0
                });
        }

        throw new IllegalArgumentException("Incorrect axis for rotation matrix.");
    }

}
