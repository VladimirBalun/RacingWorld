package ru.servers.gameServer.network;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameServer.network.protocol.toServer.LoginPacket;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class LoginPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...258] - email(254 symbols in UTF-8)
    // [259...560] - email length
    // [261...292] - password(32 symbols in UTF-8)
    // [293] - password length

    @Test
    public void gettingEmailFromPacket(){
        String testEmail = "player@gmail.com";
        byte[] email = testEmail.getBytes(StandardCharsets.UTF_8);
        byte[] buffer = new byte[LoginPacket.SIZE_PACKET];
        ByteBuffer.wrap(buffer).putShort(259, (short) testEmail.length());
        System.arraycopy(email, 0, buffer, 5, email.length);
        LoginPacket packet = new LoginPacket(buffer);
        Assert.assertEquals(testEmail, new String(packet.getEmail().getBytes()));
    }

    @Test
    public void gettingPasswordFromPacket(){
        String testPassword = "difficult_password";
        byte[] password = testPassword.getBytes(StandardCharsets.UTF_8);
        byte[] buffer = new byte[LoginPacket.SIZE_PACKET];
        buffer[293] = (byte) testPassword.length();
        System.arraycopy(password, 0, buffer, 261, password.length);
        LoginPacket packet = new LoginPacket(buffer);
        Assert.assertEquals(testPassword, packet.getPassword());
    }

    @Test(expected = IllegalArgumentException.class)
    public void settingIncorrectBufferForNetworkPacket(){
        new LoginPacket(new byte[] {});
    }

}
