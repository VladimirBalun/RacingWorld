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

package ru.servers.gameServer.logic.components;

public class Health implements Component {

    private short hp;

    private final short MIN_COUNT_HEALTH = 0;
    private final short MAX_COUNT_HEALTH = 100;

    public Health(short countHealth){
        if (countHealth > MAX_COUNT_HEALTH) {
            this.hp = MAX_COUNT_HEALTH;
        }
        if (countHealth < MIN_COUNT_HEALTH) {
            this.hp = MIN_COUNT_HEALTH;
        }
    }

    public void setHP(short newCountHealth) {
        if (newCountHealth > MAX_COUNT_HEALTH) {
            this.hp = MAX_COUNT_HEALTH;
        }
        if (newCountHealth < MIN_COUNT_HEALTH) {
            this.hp = MIN_COUNT_HEALTH;
        }
    }

    public short getHP() {
        return this.hp;
    }

}
