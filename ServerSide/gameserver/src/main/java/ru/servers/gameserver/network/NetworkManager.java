/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package ru.servers.gameserver.network;

import lombok.extern.log4j.Log4j;
import ru.servers.gameserver.ecs.ECS;
import ru.servers.gameserver.ecs.ECSGameSystem;
import ru.servers.protocol.clientwithgameserver.ErrorPacket;
import ru.servers.protocol.clientwithgameserver.PacketType;
import ru.servers.protocol.clientwithgameserver.fromserver.LoginAnswerPacket;
import ru.servers.protocol.clientwithgameserver.fromserver.LogoutAnswerPacket;
import ru.servers.protocol.clientwithgameserver.fromserver.PacketFromServer;
import ru.servers.protocol.clientwithgameserver.fromserver.WorldActionPacket;
import ru.servers.protocol.clientwithgameserver.toserver.LoginPacket;
import ru.servers.protocol.clientwithgameserver.toserver.LogoutPacket;
import ru.servers.protocol.clientwithgameserver.toserver.PlayerActionPacket;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

@Log4j
public class NetworkManager {

    private ECS gameSystem = new ECSGameSystem();

    public PacketFromServer onReceive(byte[] buffer) {
        try {
            switch (buffer[0]){
                case PacketType.LOGIN_PACKET:
                    return handleLoginPacket(buffer);
                case PacketType.PLAYER_ACTION_PACKET:
                    return handlePlayerActionPacket(buffer);
                case PacketType.LOGOUT_PACKET:
                    return handleLogoutPacket(buffer);
                default:
                    throw new IllegalArgumentException("incorrect packet type");
            }
        } catch (IllegalArgumentException e) {
            log.debug("Invalid packet. Cause: " + e.getMessage());
            return new ErrorPacket();
        }
    }

    private LoginAnswerPacket handleLoginPacket(byte[] buffer) throws IllegalArgumentException {
        LoginPacket loginPacket = new LoginPacket(buffer);
        log.debug("Login packet was received. Packet: " + loginPacket.toString());

        // TODO: add handling of request
        LoginAnswerPacket loginAnswerPacket = new LoginAnswerPacket();
        loginAnswerPacket.setPacketNumber(loginPacket.getPacketNumber());
        loginAnswerPacket.setToken(111);
        loginAnswerPacket.setResultLogin(true);
        return loginAnswerPacket;
    }

    private WorldActionPacket handlePlayerActionPacket(byte[] buffer) throws IllegalArgumentException {
        PlayerActionPacket playerActionPacket = new PlayerActionPacket(buffer);
        log.debug("Player action packet was received. Packet: " + playerActionPacket.toString());

        return new WorldActionPacket(gameSystem.getCountPlayers());
    }

    private LogoutAnswerPacket handleLogoutPacket(byte[] buffer) throws IllegalArgumentException {
        LogoutPacket logoutPacket = new LogoutPacket(buffer);
        log.debug("Logout packet was received. Packet: " + logoutPacket.toString());

        // TODO: add handling of request
        return new LogoutAnswerPacket();
    }

    public void onTimer(){
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            // TODO: add sending new location for each player
        }, 0, 20, TimeUnit.MILLISECONDS);
    }

}
