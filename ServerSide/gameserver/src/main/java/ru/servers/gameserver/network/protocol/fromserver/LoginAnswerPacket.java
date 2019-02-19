package ru.servers.gameserver.network.protocol.fromserver;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.gameserver.common.Primitives;
import ru.servers.gameserver.network.protocol.NetworkPacket;

import java.nio.ByteBuffer;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public final class LoginAnswerPacket extends NetworkPacket implements PacketFromServer{

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - result of login

    private final static byte POSITION_TOKEN = 5; // index
    private final static byte SIZE_TOKEN = Primitives.INT_SIZE; // bytes

    private final static byte POSITION_RESULT_LOGIN = 9; // index
    private final static byte SIZE_RESULT_LOGIN = Primitives.BYTE_SIZE; // bytes

    public final static byte SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_RESULT_LOGIN + SIZE_TOKEN;

    public LoginAnswerPacket(byte[] bufferFromRequest) {
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("Incorrect size of the login answer packet.");
        }
    }

    public void setToken(int token){
        ByteBuffer.wrap(buffer).putInt(POSITION_TOKEN,token);
    }

    public int getToken(){
        return ByteBuffer.wrap(buffer, POSITION_TOKEN, SIZE_TOKEN).getInt();
    }

    public void setResultLogin(boolean resultInitialization){
        buffer[POSITION_RESULT_LOGIN] = (byte) (resultInitialization ? 1 : 0);
    }

    public boolean getResultLogin(){
        return buffer[POSITION_RESULT_LOGIN] != 0;
    }

    @Override
    public byte[] getBuffer() {
        return buffer;
    }

}
