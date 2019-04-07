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

package ru.servers.databaseserver.network;

import lombok.extern.log4j.Log4j;
import ru.servers.databaseserver.data.service.MapsServiceImpl;
import ru.servers.databaseserver.data.service.RacingServiceImpl;
import ru.servers.databaseserver.data.service.RunningRacingsServiceImpl;
import ru.servers.databaseserver.data.service.UsersServiceImpl;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Properties;

@Log4j
public class DatabaseServer implements Server {

    private final int serverPort;
    private final String serverAddress;
    private final String serverRMIHostName;

    public DatabaseServer() throws RuntimeException, RemoteException {
        Properties properties = new Properties();
        try (InputStream inputStream = Files.newInputStream(Paths
                .get("databaseserver/../src/main/resources/serverSide.properties"))) {
            properties.load(inputStream);
        } catch (IOException e) {
            throw new RuntimeException("file with server properties was not read.");
        }

        serverPort = Integer.valueOf(properties.getProperty("databaseServer.port"));
        serverAddress = properties.getProperty("databaseServer.address");
        serverRMIHostName = properties.getProperty("databaseServer.rmi.hostname");
        log.info("Database server was initialized successfully");
    }

    @Override
    public void start() throws RemoteException {
        System.setProperty(serverRMIHostName, serverAddress);
        Registry registry = LocateRegistry.createRegistry(serverPort);
        registry.rebind("MapsService", new MapsServiceImpl());
        registry.rebind("UsersService", new UsersServiceImpl());
        registry.rebind("RacesService", new RacingServiceImpl());
        registry.rebind("RunningRacesService", new RunningRacingsServiceImpl());
        log.info("Database server was started successfully");
    }

}
