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

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public class LogoutAnswerPacket extends NetworkPacket implements PacketFromServer  {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5] - result of logout

    private final static byte POSITION_RESULT_LOGOUT = 9;
    private final static byte SIZE_RESULT_LOGOUT = Primitives.BYTE_SIZE;

    public final static byte SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_RESULT_LOGOUT;

    public LogoutAnswerPacket() {
        super(new byte[SIZE_PACKET]);
        buffer[POSITION_PACKET_TYPE] = PacketType.LOGOUT_ANSWER_PACKET;
    }

    @Override
    public byte[] getBuffer() {
        return buffer;
    }

}
