package ru.servers.protocol.clientwithgameserver.common;

public final class PrimitivesUtil {

    private PrimitivesUtil() {
        throw new UnsupportedOperationException("instance for class PrimitivesUtil can not be created");
    }

    public static final byte BYTE_SIZE = 1;
    public static final byte CHAR_SIZE = 2;
    public static final byte SHORT_SIZE = 2;
    public static final byte INT_SIZE = 4;
    public static final byte LONG_SIZE = 8;
    public static final byte FLOAT_SIZE = 4;
    public static final byte DOUBLE_SIZE = 8;

}
