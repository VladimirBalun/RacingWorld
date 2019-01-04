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

import ru.servers.gameServer.network.protocol.InitializePositionPacket;
import ru.servers.gameServer.network.protocol.LoginPacket;
import ru.servers.gameServer.network.protocol.NetworkPacket;
import ru.servers.gameServer.network.protocol.PacketType;

import java.util.Timer;
import java.util.TimerTask;

public class NetworkManager {

    private Timer timer = new Timer();

    public void onReceive(byte[] buffer) {
        NetworkPacket packet;
        switch (buffer[0]){
            case PacketType.LOGIN_PACKET:
                packet = new LoginPacket(buffer);
                break;
            case PacketType.LOGOUT_PACKET:
                break;
            case PacketType.INITIALIZE_POSITION_PACKET:
                packet = new InitializePositionPacket(buffer);
                break;
            case PacketType.USER_ACTION_PACKET:
                break;
        }
    }

    public void onTimer(){
        timer.schedule(new TimerTask() {
            @Override
            public void run() {



            }
        }, 0 , 20);
    }

}
