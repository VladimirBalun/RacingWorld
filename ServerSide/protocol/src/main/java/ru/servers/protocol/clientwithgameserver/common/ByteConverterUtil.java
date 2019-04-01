package ru.servers.protocol.clientwithgameserver.common;

import java.nio.ByteBuffer;

public final class ByteConverterUtil {

    private ByteConverterUtil() {
        throw new UnsupportedOperationException("instance for class ByteConverterUtil can not be created");
    }

    public static byte[] longToByteArray(long value) {
        return ByteBuffer.allocate(8).putLong(value).array();
    }

    public static byte[] floatToByteArray(float value) {
        return ByteBuffer.allocate(4).putFloat(value).array();
    }

}