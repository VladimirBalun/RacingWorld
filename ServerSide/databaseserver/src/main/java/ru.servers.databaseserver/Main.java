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

package ru.servers.databaseserver;

import lombok.extern.log4j.Log4j;
import ru.servers.databaseserver.network.DatabaseServer;
import ru.servers.databaseserver.network.Server;

import java.rmi.RemoteException;


@Log4j
public class Main {

    public static void main(String[] args) {
        try {
            log.info("Copyright 2018 Vladimir Balun - Database server.");
            log.info("Initialization of the database server...");
            Server server = new DatabaseServer();
            server.start();
        } catch (RuntimeException | RemoteException e) {
            log.error("Database server was not started. Cause: " + e.getMessage());
        }
    }

}
