package ru.servers.gameServer.network.protocol.fromServer;

import lombok.EqualsAndHashCode;
import lombok.ToString;
import ru.servers.gameServer.common.Primitives;
import ru.servers.gameServer.network.protocol.NetworkPacket;

import java.nio.ByteBuffer;

@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public final class InitializePositionAnswerPacket extends NetworkPacket implements PacketFromServer{

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5...8] - player token
    // [9] - result initialization of position

    private final static byte POSITION_TOKEN = 5; // index
    private final static byte SIZE_TOKEN = Primitives.INT_SIZE; // bytes

    private final static byte POSITION_RESULT_INITIALIZATION = 9; // index
    private final static byte SIZE_RESULT_INITIALIZATION = Primitives.BYTE_SIZE; // bytes

    public final static byte SIZE_PACKET = SIZE_NETWORK_PACKET + SIZE_RESULT_INITIALIZATION + SIZE_TOKEN;

    public InitializePositionAnswerPacket(byte[] bufferFromRequest) {
        super(bufferFromRequest);
        if (bufferFromRequest.length < SIZE_PACKET){
            throw new IllegalArgumentException("Incorrect size of the initialize position answer packet.");
        }
    }

    public void setToken(int token){
        ByteBuffer.wrap(buffer).putInt(POSITION_TOKEN,token);
    }

    public int getToken(){
        return ByteBuffer.wrap(buffer, POSITION_TOKEN, SIZE_TOKEN).getInt();
    }

    public void setResultInitialization(boolean resultInitialization){
        buffer[POSITION_RESULT_INITIALIZATION] = (byte) (resultInitialization ? 1 : 0);
    }

    public boolean getResultInitialization(){
        return buffer[POSITION_RESULT_INITIALIZATION] != 0;
    }

    @Override
    public byte[] getBuffer() {
        return buffer;
    }

}
