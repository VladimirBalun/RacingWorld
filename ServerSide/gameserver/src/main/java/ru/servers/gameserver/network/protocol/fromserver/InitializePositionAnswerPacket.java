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

package ru.servers.gameserver.network.protocol.fromserver;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.gameserver.common.Primitives;
import ru.servers.gameserver.network.protocol.NetworkPacket;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public final class InitializePositionAnswerPacket extends NetworkPacket implements PacketFromServer{

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5] - result initialization of position

    private final static byte POSITION_RESULT_INITIALIZATION = 5; // index
    private final static byte SIZE_RESULT_INITIALIZATION = Primitives.BYTE_SIZE; // bytes

    public final static byte SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_RESULT_INITIALIZATION ;

    public InitializePositionAnswerPacket(byte[] bufferFromRequest) {
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("Incorrect size of the initialize position answer packet.");
        }
    }

    public void setResultInitialization(boolean resultInitialization){
        buffer[POSITION_RESULT_INITIALIZATION] = (byte) (resultInitialization ? 1 : 0);
    }

    public boolean getResultInitialization(){
        return buffer[POSITION_RESULT_INITIALIZATION] != 0;
    }

    @Override
    public byte[] getBuffer() {
        return buffer;
    }

}
