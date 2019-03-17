package ru.servers.protocol;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.protocol.clientwithgameserver.fromserver.LogoutAnswerPacket;

public class LogoutAnswerPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5] - result of logout

    @Test
    public void settingResultLogout(){
        LogoutAnswerPacket packet = new LogoutAnswerPacket();
        packet.setResultLogout(true);
        Assert.assertTrue(packet.getResultLogout());
    }

}
