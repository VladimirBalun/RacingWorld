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

package ru.servers.gameserver.network.connectors;

import ru.servers.protocol.gameserverwithdatabaseserver.service.MapsService;
import ru.servers.protocol.gameserverwithdatabaseserver.service.RacingService;
import ru.servers.protocol.gameserverwithdatabaseserver.service.RunningRacingsService;
import ru.servers.protocol.gameserverwithdatabaseserver.service.UsersService;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.rmi.Naming;
import java.util.*;

public class DatabaseServerConnector {

    private UsersService usersService;
    private RacingService racingService;
    private RunningRacingsService runningRacingsService;
    private MapsService mapsService;

    public DatabaseServerConnector() throws Exception {
        Properties properties = new Properties();
        try (InputStream inputStream = Files.newInputStream(Paths
                .get("gameserver/../src/main/resources/serverSide.properties"))){
            properties.load(inputStream);
        } catch (IOException e) {
            throw new IOException("file with server properties was not read.");
        }

        usersService = (UsersService) Naming.lookup(properties.getProperty("databaseServer.usersService.path"));
        racingService = (RacingService) Naming.lookup(properties.getProperty("databaseServer.racesService.path"));
        runningRacingsService = (RunningRacingsService) Naming.lookup(properties.getProperty("databaseServer.runningRacingsService.path"));
        mapsService = (MapsService) Naming.lookup(properties.getProperty("databaseServer.mapsService.path"));
    }

    public UsersService getUsersService() {
        return usersService;
    }

    public RacingService getRacesService(){
        return racingService;
    }

    public RunningRacingsService getRunningRacingsService(){
        return runningRacingsService;
    }

    public MapsService getMapsService(){
        return mapsService;
    }

}
