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

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.protocol.clientwithgameserver.common.PrimitivesUtil;

import java.nio.ByteBuffer;

@ToString
@EqualsAndHashCode
public class NetworkPacket {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number

    protected byte[] buffer;

    protected final static byte POSITION_PACKET_TYPE = 0;
    protected final static byte SIZE_PACKET_TYPE = PrimitivesUtil.BYTE_SIZE;

    protected final static byte POSITION_PACKET_NUMBER = 1;
    protected final static byte SIZE_PACKET_NUMBER = PrimitivesUtil.INT_SIZE;

    protected final static byte SIZE_NETWORK_PACKET = SIZE_PACKET_TYPE + SIZE_PACKET_NUMBER;

    public NetworkPacket(byte[] bufferFromRequest){
        if (bufferFromRequest.length >= SIZE_PACKET_NUMBER){
            buffer = bufferFromRequest;
        } else {
            throw new IllegalArgumentException("incorrect size of the packet.");
        }
    }

    public byte getPacketType(){
        return buffer[POSITION_PACKET_TYPE];
    }

    public void setPacketType(byte packetType){
        buffer[POSITION_PACKET_TYPE] = packetType;
    }

    public int getPacketNumber(){
        return ByteBuffer.wrap(buffer, POSITION_PACKET_NUMBER, SIZE_PACKET_NUMBER).getInt();
    }

    public void setPacketNumber(int packetNumber){
        ByteBuffer.wrap(buffer).putInt(POSITION_PACKET_NUMBER, packetNumber);
    }

}
