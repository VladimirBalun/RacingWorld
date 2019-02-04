package ru.servers.game.network.protocol;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.game.network.protocol.fromserver.PacketFromServer;
import ru.servers.game.network.protocol.toserver.PacketToServer;

@ToString
@EqualsAndHashCode
public final class ErrorPacket implements PacketFromServer, PacketToServer {

    private byte buffer = PacketType.ERROR_PACKET;

    @Override
    public byte[] getBuffer() {
        return new byte[]{ buffer };
    }

}
