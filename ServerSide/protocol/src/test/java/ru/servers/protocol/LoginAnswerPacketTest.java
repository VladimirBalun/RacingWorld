package ru.servers.protocol;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.protocol.clientwithgameserver.fromserver.LoginAnswerPacket;

public class LoginAnswerPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - result of login

    @Test
    public void settingToken(){
        int token = 111;
        LoginAnswerPacket packet = new LoginAnswerPacket();
        packet.setToken(token);
        Assert.assertEquals(token, packet.getToken());
    }

    @Test
    public void settingResultInitialization(){
        LoginAnswerPacket packet = new LoginAnswerPacket();
        packet.setResultLogin(true);
        Assert.assertTrue(packet.getResultLogin());
    }

}
