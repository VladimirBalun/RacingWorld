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

package ru.servers.gameServer.network;

import ru.servers.gameServer.network.protocol.*;
import ru.servers.gameServer.network.protocol.fromServer.InitializePositionAnswerPacket;
import ru.servers.gameServer.network.protocol.fromServer.LoginAnswerPacket;
import ru.servers.gameServer.network.protocol.fromServer.PacketFromServer;
import ru.servers.gameServer.network.protocol.toServer.InitializePositionPacket;
import ru.servers.gameServer.network.protocol.toServer.LoginPacket;
import ru.servers.gameServer.network.protocol.toServer.PacketToServer;

import java.util.Timer;
import java.util.TimerTask;

public class NetworkManager {

    private Timer timer = new Timer();

    public PacketFromServer onReceive(byte[] buffer) {
        PacketToServer packet;
        byte[] bufferFromServer;
        switch (buffer[0]){
            case PacketType.LOGIN_PACKET:
                packet = new LoginPacket(buffer);
                // TODO: add handling of request
                bufferFromServer = new byte[LoginAnswerPacket.SIZE_PACKET];
                LoginAnswerPacket loginAnswerPacket = new LoginAnswerPacket(bufferFromServer);
                loginAnswerPacket.setPacketType(PacketType.INITIALIZE_POSITION_ANSWER_PACKET);
                loginAnswerPacket.setPacketNumber(((LoginPacket) packet).getPacketNumber());
                loginAnswerPacket.setToken(111);
                loginAnswerPacket.setResultLogin(true);
                return loginAnswerPacket;
            case PacketType.INITIALIZE_POSITION_PACKET:
                packet = new InitializePositionPacket(buffer);
                // TODO: add handling of request
                bufferFromServer = new byte[InitializePositionAnswerPacket.SIZE_PACKET];
                InitializePositionAnswerPacket initializePositionAnswerPacket = new InitializePositionAnswerPacket(bufferFromServer);
                initializePositionAnswerPacket.setPacketType(PacketType.INITIALIZE_POSITION_ANSWER_PACKET);
                initializePositionAnswerPacket.setPacketNumber(((InitializePositionPacket) packet).getPacketNumber());
                initializePositionAnswerPacket.setToken(111);
                initializePositionAnswerPacket.setResultInitialization(true);
                return initializePositionAnswerPacket;
            default:
                return new ErrorPacket();
        }
    }

    public void onTimer(){
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                // TODO: add tasks by timer
            }
        }, 0 , 20);
    }

}
