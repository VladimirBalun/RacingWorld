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

package ru.servers.gameserver.network.protocol.toserver;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.gameserver.common.Primitives;
import ru.servers.gameserver.math.algebra.vectors.Vector3;
import ru.servers.gameserver.network.protocol.NetworkPacket;

import java.nio.ByteBuffer;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public final class InitializePositionPacket extends NetworkPacket implements PacketFromClient {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9...19] - position - x[9...12], y[13...16], z[17...20]
    // [21...28] - direction - x[21...24], y[25...28]. z[29...32]

    private final static byte POSITION_TOKEN = 5; // index
    private final static byte SIZE_TOKEN = Primitives.INT_SIZE;

    private final static byte POSITION_OF_VECTOR_POSITION = 9; // index
    private final static byte POSITION_OF_VECTOR_DIRECTION = 21; // index
    private final static byte SIZE_ONE_VECTOR_ELEMENT = Primitives.FLOAT_SIZE; // bytes

    public final static short SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_TOKEN + ((SIZE_ONE_VECTOR_ELEMENT * 4) * 2);

    public InitializePositionPacket(byte[] bufferFromRequest){
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("Size of the initialize position packet is incorrect.");
        }
    }

    public int getToken(){
        return ByteBuffer.wrap(buffer, POSITION_TOKEN, SIZE_TOKEN).getInt();
    }

    public Vector3 getPosition(){
        return convertBufferBytesToVector3(POSITION_OF_VECTOR_POSITION);
    }

    public Vector3 getDirection(){
        return convertBufferBytesToVector3(POSITION_OF_VECTOR_DIRECTION);
    }

    private Vector3 convertBufferBytesToVector3(int startFromByte){
        final float x = ByteBuffer.wrap(buffer, startFromByte, SIZE_ONE_VECTOR_ELEMENT).getFloat();
        final float y = ByteBuffer.wrap(buffer, startFromByte + SIZE_ONE_VECTOR_ELEMENT, SIZE_ONE_VECTOR_ELEMENT).getFloat();
        final float z = ByteBuffer.wrap(buffer, startFromByte + SIZE_ONE_VECTOR_ELEMENT + SIZE_ONE_VECTOR_ELEMENT, SIZE_ONE_VECTOR_ELEMENT).getFloat();
        return new Vector3(x, y, z);
    }

}
