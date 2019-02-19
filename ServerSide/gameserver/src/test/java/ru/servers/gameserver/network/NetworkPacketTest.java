package ru.servers.gameserver.network;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameserver.network.protocol.NetworkPacket;
import ru.servers.gameserver.network.protocol.PacketType;

public class NetworkPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number

    private NetworkPacket networkPacket = new NetworkPacket(new byte[] {
            PacketType.LOGIN_PACKET, // Packet type
            0x00, 0x00, 0x00, 0x55 // Packet number(85 in dec system)
    });

    @Test
    public void gettingPacketType(){
        Assert.assertEquals(PacketType.LOGIN_PACKET, networkPacket.getPacketType());
    }

    @Test
    public void gettingPacketNumber(){
        Assert.assertEquals(85, networkPacket.getPacketNumber());
    }

    @Test(expected = IllegalArgumentException.class)
    public void settingIncorrectBufferForNetworkPacket(){
        new NetworkPacket(new byte[] {});
    }

}
