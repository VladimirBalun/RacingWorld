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

package ru.servers.protocol.clientwithgameserver.toserver;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.protocol.clientwithgameserver.common.Primitives;
import ru.servers.protocol.clientwithgameserver.NetworkPacket;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public class PlayerActionPacket extends NetworkPacket implements PacketFromClient {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - W key state(is pressed or not)
    // [10] - S key state(is pressed or not)
    // [11] - A key state(is pressed or not)
    // [12] - D key state(is pressed or not)

    private final static byte POSITION_TOKEN = 5;
    private final static byte SIZE_TOKEN = Primitives.INT_SIZE;

    private final static byte POSITION_W_KEY_STATE = 9;
    private final static byte SIZE_W_KEY_STATE = Primitives.BYTE_SIZE;

    private final static byte POSITION_S_KEY_STATE = 10;
    private final static byte SIZE_S_KEY_STATE = Primitives.BYTE_SIZE;

    private final static byte POSITION_A_KEY_STATE = 11;
    private final static byte SIZE_A_KEY_STATE = Primitives.BYTE_SIZE;

    private final static byte POSITION_D_KEY_STATE = 12;
    private final static byte SIZE_D_KEY_STATE = Primitives.BYTE_SIZE;

    public final static short SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_TOKEN +
            SIZE_W_KEY_STATE + SIZE_S_KEY_STATE + SIZE_A_KEY_STATE + SIZE_D_KEY_STATE;

    public PlayerActionPacket(byte[] bufferFromRequest) {
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("incorrect size of the player action packet.");
        }
    }

}
