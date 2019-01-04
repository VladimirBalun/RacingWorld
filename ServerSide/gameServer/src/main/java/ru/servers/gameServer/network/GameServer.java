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

import lombok.extern.log4j.Log4j;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;

@Log4j
public class GameServer implements Server {

    private boolean isListening;
    private ServerSocket serverSocket;

    public GameServer(int port) throws IOException {
        serverSocket = new ServerSocket(port);
    }

    @Override
    public void startServer(int maxCountConnections){
        ExecutorService threadPool = Executors.newFixedThreadPool(maxCountConnections);
        Semaphore semaphore = new Semaphore(maxCountConnections);
        isListening = true;

        while (isListening) {
            threadPool.execute(() -> {
                try {
                    semaphore.acquire();
                    Socket clientSocket = serverSocket.accept();
                    InputStream inputStream = clientSocket.getInputStream();
                    OutputStream outputStream = clientSocket.getOutputStream();
                    // TODO: handling of request
                } catch (IOException | InterruptedException e) {
                    log.error("Error during working with request. Cause:" + e.getMessage());
                } finally {
                    semaphore.release();
                }
            });
        }
    }

    @Override
    public void stopServer() throws IOException {
        isListening = false;
        serverSocket.close();
    }

}
