package ru.servers.gameServer.network;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.network.protocol.toServer.LoginPacket;

public class LoginPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...513] - email(254 symbols in UTF-8)
    // [514] - email length
    // [515...578] - password(32 symbols in UTF-8)
    // [579] - password length

    @Test
    public void gettingEmailFromPacket(){
        String testEmail = "tester@gmail.com";
        byte[] email = testEmail.getBytes();
        byte[] buffer = new byte[LoginPacket.SIZE_PACKET];
        buffer[514] = (byte) testEmail.length();
        System.arraycopy(email, 0, buffer, 5, email.length);
        LoginPacket packet = new LoginPacket(buffer);
        Assert.assertEquals(testEmail, packet.getEmail());
    }

    @Test
    public void gettingPasswordFromPacket(){
        String testPassword = "12345";
        byte[] password = testPassword.getBytes();
        byte[] buffer = new byte[LoginPacket.SIZE_PACKET];
        buffer[579] = (byte) testPassword.length();
        System.arraycopy(password, 0, buffer, 515, password.length);
        LoginPacket packet = new LoginPacket(buffer);
        Assert.assertEquals(testPassword, packet.getPassword());
    }

    @Test(expected = IllegalArgumentException.class)
    public void settingIncorrectBufferForNetworkPacket(){
        new LoginPacket(new byte[] {});
    }

}
