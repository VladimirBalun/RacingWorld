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

package ru.servers.protocol.clientwithgameserver.fromserver;

import lombok.EqualsAndHashCode;
import lombok.ToString;


import ru.servers.protocol.clientwithgameserver.common.Primitives;
import ru.servers.protocol.clientwithgameserver.NetworkPacket;
import ru.servers.protocol.clientwithgameserver.PacketType;


import java.nio.ByteBuffer;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public class WorldActionPacket extends NetworkPacket implements PacketFromServer {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5] - count players
    // for (byte i = 0; i < count players; i++)
    //   [(START_POSITION_PLAYER_POSITION + (PLAYER_LOCATION_SIZE * i))...((START_POSITION_PLAYER_POSITION + (PLAYER_LOCATION_SIZE * i) + VECTOR_SIZE - 1)] - position
    //   [(START_POSITION_PLAYER_DIRECTION + (PLAYER_LOCATION_SIZE * i))...((START_POSITION_PLAYER_DIRECTION + (PLAYER_LOCATION_SIZE * i) + VECTOR_SIZE - 1)] - direction

    private final byte countPlayers;

    private final static byte POSITION_COUNT_PLAYERS = 5;
    private final static byte SIZE_COUNT_PLAYERS = Primitives.BYTE_SIZE;

    private final static byte START_POSITION_PLAYER_POSITION = 6;
    private final static byte START_POSITION_PLAYER_DIRECTION = 18;
    private final static byte VECTOR_SIZE = Primitives.FLOAT_SIZE * 3;
    private final static byte PLAYER_LOCATION_SIZE = VECTOR_SIZE * 2;

    private final static byte SIZE_PACKET_WITHOUT_PLAYERS = SIZE_NETWORK_PACKET + SIZE_COUNT_PLAYERS;

    public WorldActionPacket(int countPlayers) {
        super(new byte[SIZE_PACKET_WITHOUT_PLAYERS + (countPlayers * PLAYER_LOCATION_SIZE)]);
        this.countPlayers = (byte) countPlayers;
        buffer[POSITION_PACKET_TYPE] = PacketType.WORLD_ACTION_PACKET;
        buffer[POSITION_COUNT_PLAYERS] = this.countPlayers;
    }

    private void checkingNumberPlayer(int numberPlayer) {
        if (countPlayers < numberPlayer){
            throw new IllegalArgumentException("incorrect player number.");
        }
    }

    public void setPositionPlayer(int numberPlayer, float xPos, float yPos, float zPos) {
        checkingNumberPlayer(numberPlayer);
        ByteBuffer.wrap(buffer).putFloat(START_POSITION_PLAYER_POSITION + PLAYER_LOCATION_SIZE * (numberPlayer - 1), xPos);
        ByteBuffer.wrap(buffer).putFloat(START_POSITION_PLAYER_POSITION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE, yPos);
        ByteBuffer.wrap(buffer).putFloat(START_POSITION_PLAYER_POSITION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE * 2, zPos);
    }

    public void setDirectionPlayer(int numberPlayer, float xDir, float yDir, float zDir){
        checkingNumberPlayer(numberPlayer);
        ByteBuffer.wrap(buffer).putFloat(START_POSITION_PLAYER_DIRECTION + PLAYER_LOCATION_SIZE * (numberPlayer - 1), xDir);
        ByteBuffer.wrap(buffer).putFloat(START_POSITION_PLAYER_DIRECTION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE, yDir);
        ByteBuffer.wrap(buffer).putFloat(START_POSITION_PLAYER_DIRECTION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE * 2, zDir);
    }

    /* TODO: 19.03.2019 add methods getPosition and getDirection after rendering module Math
    public Vector3 getPositionPlayer(int numberPlayer){
        return new Vector3(
                ByteBuffer.wrap(buffer).getFloat(START_POSITION_PLAYER_POSITION + PLAYER_LOCATION_SIZE * (numberPlayer - 1)),
                ByteBuffer.wrap(buffer).getFloat(START_POSITION_PLAYER_POSITION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE),
                ByteBuffer.wrap(buffer).getFloat(START_POSITION_PLAYER_POSITION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE * 2),
        );
    }
    public Vector3 getDirectionPlayer(int numberPlayer){
        return new Vector3(
                ByteBuffer.wrap(buffer).getFloat(START_POSITION_PLAYER_DIRECTION + PLAYER_LOCATION_SIZE * (numberPlayer - 1)),
                ByteBuffer.wrap(buffer).getFloat(START_POSITION_PLAYER_DIRECTION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE),
                ByteBuffer.wrap(buffer).getFloat(START_POSITION_PLAYER_DIRECTION + PLAYER_LOCATION_SIZE * (numberPlayer - 1) + Primitives.FLOAT_SIZE * 2),
        );
    }
    */

    public int getCountPlayers(){
        return buffer[POSITION_COUNT_PLAYERS];
    }


    @Override
    public byte[] getBuffer() {
        return buffer;
    }

}
