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

package ru.servers.gameserver.ecs.components;

import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;

@ToString
@EqualsAndHashCode
@NoArgsConstructor
public class Mass implements Component {

    private int mass; // kilograms

    public final int MIN_COUNT_MASS = 0;
    public final int MAX_COUNT_MASS = 10_000;

    public Mass(int mass){
        if (mass > MAX_COUNT_MASS) {
            this.mass = MAX_COUNT_MASS;
        }
        if (mass < MIN_COUNT_MASS) {
            this.mass = MIN_COUNT_MASS;
        }
    }

    public void setMass(int newMass) {
        if (newMass > MAX_COUNT_MASS) {
            mass = MAX_COUNT_MASS;
        }
        if (newMass < MIN_COUNT_MASS) {
            mass = MIN_COUNT_MASS;
        }
    }

    public int getMass() {
        return mass;
    }

    @Override
    public Mass clone() {
        try {
            return (Mass)super.clone();
        }
        catch (CloneNotSupportedException e) {
            throw new InternalError();
        }
    }

}