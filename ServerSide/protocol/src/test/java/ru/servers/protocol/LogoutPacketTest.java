package ru.servers.protocol;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.protocol.clientwithgameserver.toserver.LogoutPacket;

import java.nio.ByteBuffer;

public class LogoutPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token

    @Test
    public void gettingToken() {
        int testToken = 65412876;
        byte[] buffer = new byte[LogoutPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).putInt(5, testToken);
        LogoutPacket packet = new LogoutPacket(buffer);
        Assert.assertEquals(testToken, packet.getToken());
    }
}
