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

public class Matrices2x2 {

    public static Matrix2x2 getIdentity(){
        return new Matrix2x2(new double[] {
                1.0, 0.0,
                0.0, 1.0
        });
    }

    public static Matrix2x2 getRotation(double angle){
        return new Matrix2x2(new double[] {
                Math.cos(angle), -Math.sin(angle),
                Math.sin(angle), Math.cos(angle)
        });
    }

}
