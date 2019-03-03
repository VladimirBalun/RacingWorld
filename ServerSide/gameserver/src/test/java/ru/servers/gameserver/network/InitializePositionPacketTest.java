package ru.servers.gameserver.network;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameserver.math.algebra.vectors.Vector3;
import ru.servers.gameserver.network.protocol.toserver.InitializePositionPacket;

import java.nio.ByteBuffer;

public class InitializePositionPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9...19] - position - x[9...12], y[13...16], z[17...20]
    // [21...28] - direction - x[21...24], y[25...28]. z[29...32]

    @Test
    public void gettingTokenFromPacket(){
        int token = 111;
        byte[] buffer = new byte[InitializePositionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).putInt(5,token);
        InitializePositionPacket packet = new InitializePositionPacket(buffer);
        Assert.assertEquals(token, packet.getToken());
    }

    @Test
    public void gettingPositionFromPacket(){
        byte[] buffer = new byte[InitializePositionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).putFloat(9,1.0f);
        ByteBuffer.wrap(buffer).putFloat(13,2.0f);
        ByteBuffer.wrap(buffer).putFloat(17,3.0f);
        InitializePositionPacket packet = new InitializePositionPacket(buffer);
        Assert.assertEquals(new Vector3(1.0f, 2.0f, 3.0f), packet.getPosition());
    }

    @Test
    public void gettingDirectionFromPacket(){
        byte[] buffer = new byte[InitializePositionPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).putFloat(21,4.0f);
        ByteBuffer.wrap(buffer).putFloat(25,5.0f);
        ByteBuffer.wrap(buffer).putFloat(29,6.0f);
        InitializePositionPacket packet = new InitializePositionPacket(buffer);
        Assert.assertEquals(new Vector3(4.0f, 5.0f, 6.0f), packet.getDirection());
    }

    @Test(expected = IllegalArgumentException.class)
    public void settingIncorrectBufferForNetworkPacket(){
        new InitializePositionPacket(new byte[]{});
    }

}
