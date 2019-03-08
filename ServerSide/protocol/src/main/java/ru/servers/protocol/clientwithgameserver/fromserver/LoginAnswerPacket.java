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
import ru.servers.gameserver.network.protocol.PacketType;

import java.nio.ByteBuffer;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public final class LoginAnswerPacket extends NetworkPacket implements PacketFromServer{

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - result of login

    private final static byte POSITION_TOKEN = 5;
    private final static byte SIZE_TOKEN = Primitives.INT_SIZE;

    private final static byte POSITION_RESULT_LOGIN = 9;
    private final static byte SIZE_RESULT_LOGIN = Primitives.BYTE_SIZE;

    public final static byte SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_RESULT_LOGIN + SIZE_TOKEN;

    public LoginAnswerPacket() {
        super(new byte[SIZE_PACKET]);
        buffer[POSITION_PACKET_TYPE] = PacketType.LOGIN_ANSWER_PACKET;
    }

    public void setToken(int token){
        ByteBuffer.wrap(buffer).putInt(POSITION_TOKEN,token);
    }

    public int getToken(){
        return ByteBuffer.wrap(buffer, POSITION_TOKEN, SIZE_TOKEN).getInt();
    }

    public void setResultLogin(boolean resultInitialization){
        buffer[POSITION_RESULT_LOGIN] = (byte) (resultInitialization ? 1 : 0);
    }

    public boolean getResultLogin(){
        return buffer[POSITION_RESULT_LOGIN] != 0;
    }

    @Override
    public byte[] getBuffer() {
        return buffer;
    }

}
