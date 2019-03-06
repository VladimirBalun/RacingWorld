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
import ru.servers.gameserver.network.protocol.*;
import ru.servers.gameserver.network.protocol.fromserver.InitializePositionAnswerPacket;
import ru.servers.gameserver.network.protocol.fromserver.LoginAnswerPacket;
import ru.servers.gameserver.network.protocol.fromserver.PacketFromServer;
import ru.servers.gameserver.network.protocol.toserver.InitializePositionPacket;
import ru.servers.gameserver.network.protocol.toserver.LoginPacket;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

@Log4j
public class NetworkManager {

    private ECS gameSystem = new ECSGameSystem();

    public PacketFromServer onReceive(byte[] buffer) {
        switch (buffer[0]){
            case PacketType.LOGIN_PACKET:
                return handleLoginPacket(buffer);
            case PacketType.INITIALIZE_POSITION_PACKET:
                return handleInitializePositionPacket(buffer);
            default:
                log.debug("Error packet was received.");
                return new ErrorPacket();
        }
    }

    private LoginAnswerPacket handleLoginPacket(byte[] bufferFromClient) {
        LoginPacket packet = new LoginPacket(bufferFromClient);
        log.debug("Login packet was received. Packet: " + packet.toString());

        // TODO: add handling of request
        byte[] bufferFromServer = new byte[LoginAnswerPacket.SIZE_PACKET];
        LoginAnswerPacket loginAnswerPacket = new LoginAnswerPacket(bufferFromServer);
        loginAnswerPacket.setPacketType(PacketType.INITIALIZE_POSITION_ANSWER_PACKET);
        loginAnswerPacket.setPacketNumber(packet.getPacketNumber());
        loginAnswerPacket.setToken(111);
        loginAnswerPacket.setResultLogin(true);
        return loginAnswerPacket;
    }

    private InitializePositionAnswerPacket handleInitializePositionPacket(byte[] bufferFromClient){
        InitializePositionPacket packet = new InitializePositionPacket(bufferFromClient);
        log.debug("Initialize position packet was received. Packet: " + packet.toString());

        // TODO: add handling of request
        byte[] bufferFromServer = new byte[InitializePositionAnswerPacket.SIZE_PACKET];
        InitializePositionAnswerPacket initializePositionAnswerPacket = new InitializePositionAnswerPacket(bufferFromServer);
        initializePositionAnswerPacket.setPacketType(PacketType.INITIALIZE_POSITION_ANSWER_PACKET);
        initializePositionAnswerPacket.setPacketNumber(packet.getPacketNumber());
        initializePositionAnswerPacket.setResultInitialization(true);
        return initializePositionAnswerPacket;
    }

    public void onTimer(){
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            // TODO: add sending new location for each player
        }, 0, 20, TimeUnit.MILLISECONDS);
    }

}
