package ru.servers.protocol;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.protocol.clientwithgameserver.toserver.PlayerActionPacket;

import java.nio.ByteBuffer;

public class PlayerActionPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - W key state(is pressed or not)
    // [10] - S key state(is pressed or not)
    // [11] - A key state(is pressed or not)
    // [12] - D key state(is pressed or not)

    @Test
    public void gettingToken() {
        int testToken = 568742;
        byte[] buffer = new byte[PlayerActionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).putInt(5, testToken);
        PlayerActionPacket packet = new PlayerActionPacket(buffer);
        Assert.assertEquals(testToken, packet.getToken());
    }

    @Test
    public void gettingWKeyStatus(){
        byte wKeyStatus = 1; // true
        byte[] buffer = new byte[PlayerActionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).put(9, wKeyStatus);
        PlayerActionPacket packet = new PlayerActionPacket(buffer);
        Assert.assertTrue(packet.getWKeyStatus());
    }

    @Test
    public void gettingSKeyStatus(){
        byte sKeyStatus = 1; // true
        byte[] buffer = new byte[PlayerActionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).put(10, sKeyStatus);
        PlayerActionPacket packet = new PlayerActionPacket(buffer);
        Assert.assertTrue(packet.getSKeyStatus());
    }

    @Test
    public void gettingAKeyStatus(){
        byte aKeyStatusByte = 1; // true
        byte[] buffer = new byte[PlayerActionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).put(11, aKeyStatusByte);
        PlayerActionPacket packet = new PlayerActionPacket(buffer);
        Assert.assertTrue(packet.getAKeyStatus());
    }

    @Test
    public void gettingDKeyStatus(){
        byte dKeyStatusByte = 1; // true
        byte[] buffer = new byte[PlayerActionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).put(12, dKeyStatusByte);
        PlayerActionPacket packet = new PlayerActionPacket(buffer);
        Assert.assertTrue(packet.getDKeyStatus());
    }

}
