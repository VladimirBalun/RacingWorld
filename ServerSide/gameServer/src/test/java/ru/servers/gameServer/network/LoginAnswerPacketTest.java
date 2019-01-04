package ru.servers.gameServer.network;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.network.protocol.fromServer.LoginAnswerPacket;


public class LoginAnswerPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - result of login

    @Test
    public void settingToken(){
        int token = 111;
        byte[] buffer = new byte[LoginAnswerPacket.SIZE_PACKET];
        LoginAnswerPacket packet = new LoginAnswerPacket(buffer);
        packet.setToken(token);
        Assert.assertEquals(token, packet.getToken());
    }

    @Test
    public void settingResultInitialization(){
        byte[] buffer = new byte[LoginAnswerPacket.SIZE_PACKET];
        LoginAnswerPacket packet = new LoginAnswerPacket(buffer);
        packet.setResultLogin(true);
        Assert.assertTrue(packet.getResultLogin());
    }

    @Test(expected = IllegalArgumentException.class)
    public void settingIncorrectBufferForNetworkPacket(){
        new LoginAnswerPacket(new byte[]{});
    }

}
