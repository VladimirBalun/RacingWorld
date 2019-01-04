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

package ru.servers.gameServer.network.protocol.toServer;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.gameServer.common.Primitives;
import ru.servers.gameServer.network.protocol.NetworkPacket;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public final class LoginPacket extends NetworkPacket implements PacketToServer {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...513] - email(254 symbols in UTF-8)
    // [514] - email length
    // [515...578] - password(32 symbols in UTF-8)
    // [579] - password length

    private final static byte POSITION_EMAIL = 5; // index
    private final static short SIZE_EMAIL = 254 * Primitives.CHAR_SIZE; // bytes

    private final static short POSITION_OF_SIZE_EMAIL = 514; // index
    private final static short POSITION_OF_SIZE_PASSWORD = 579; // index
    private final static byte SIZE_OF_EMAIL_AND_PASSWORD_SIZES = Primitives.BYTE_SIZE * 2; // bytes

    private final static short POSITION_PASSWORD = 515; // index
    private final static short SIZE_PASSWORD = 32 * Primitives.CHAR_SIZE; // bytes

    public final static short SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_EMAIL + SIZE_PASSWORD + SIZE_OF_EMAIL_AND_PASSWORD_SIZES;

    public LoginPacket(byte[] bufferFromRequest){
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("Incorrect size of the login packet.");
        }
    }

    public String getEmail(){
        return new String(buffer, POSITION_EMAIL, buffer[POSITION_OF_SIZE_EMAIL]);
    }

    public String getPassword(){
        return new String(buffer, POSITION_PASSWORD, buffer[POSITION_OF_SIZE_PASSWORD]);
    }

}
