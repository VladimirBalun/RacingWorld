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
import ru.servers.protocol.clientwithgameserver.common.PrimitivesUtil;
import ru.servers.protocol.clientwithgameserver.NetworkPacket;

import java.nio.ByteBuffer;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public class LogoutPacket extends NetworkPacket implements PacketFromClient {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token

    private final static byte POSITION_TOKEN = 5;
    private final static byte SIZE_TOKEN = PrimitivesUtil.INT_SIZE;

    public final static short SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_TOKEN;

    public LogoutPacket(byte[] bufferFromRequest) {
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("incorrect size of the logout packet.");
        }
    }

    public int getToken() {
        return ByteBuffer.wrap(buffer, POSITION_TOKEN, SIZE_TOKEN).getInt();
    }

}
