package ru.servers.gameServer.network.protocol;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.gameServer.network.protocol.fromServer.PacketFromServer;
import ru.servers.gameServer.network.protocol.toServer.PacketToServer;

@ToString
@EqualsAndHashCode
public final class ErrorPacket implements PacketFromServer, PacketToServer {

    private byte buffer = PacketType.ERROR_PACKET;

    @Override
    public byte[] getBuffer() {
        return new byte[]{ buffer };
    }

}
