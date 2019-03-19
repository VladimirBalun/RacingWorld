package ru.servers.protocol;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.protocol.clientwithgameserver.fromserver.WorldActionPacket;

public class WorldActionPacketTest {

    // Byte protocol:
    // [0] - protocol type
    // [1...4] - packet number
    // [5] - count players
    // for (byte i = 0; i < count players; i++)
    //   [(START_POSITION_PLAYER_POSITION + (PLAYER_LOCATION_SIZE * i))...((START_POSITION_PLAYER_POSITION + (PLAYER_LOCATION_SIZE * i) + VECTOR_SIZE - 1)] - position
    //   [(START_POSITION_PLAYER_DIRECTION + (PLAYER_LOCATION_SIZE * i))...((START_POSITION_PLAYER_DIRECTION + (PLAYER_LOCATION_SIZE * i) + VECTOR_SIZE - 1)] - direction

    @Test
    public void gettingPlayers() {
        int countPlayers = 43;
        WorldActionPacket packet = new WorldActionPacket(countPlayers);
        Assert.assertEquals(countPlayers, packet.getCountPlayers());
    }

}
