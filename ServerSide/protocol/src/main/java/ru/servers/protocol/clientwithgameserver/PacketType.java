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

package ru.servers.protocol.clientwithgameserver;

public class PacketType {

    public static final byte ERROR_PACKET = 0;
    public static final byte LOGIN_PACKET = 1;
    public static final byte LOGIN_ANSWER_PACKET = 2;
    public static final byte LOGOUT_PACKET = 3;
    public static final byte LOGOUT_ANSWER_PACKET = 4;
    public static final byte PLAYER_ACTION_PACKET = 7;
    public static final byte WORLD_ACTION_PACKET = 8;

}
