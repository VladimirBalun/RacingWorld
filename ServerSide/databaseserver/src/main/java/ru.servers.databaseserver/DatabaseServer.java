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
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;

@Log4j
public class DatabaseServer implements Server {

    private boolean isListening;
    private ServerSocket serverSocket;
    private static BufferedReader in;
    private static BufferedWriter out;
    private Socket connectionSocket;

    public DatabaseServer(int port) throws IOException {
        serverSocket = new ServerSocket(port);
    }

    @Override
    public void startServer(int maxCountConnections){
        ExecutorService threadPool = Executors.newFixedThreadPool(maxCountConnections);
        Semaphore semaphore = new Semaphore(maxCountConnections);
        log.info("Database server started successfully.");
        isListening = true;

        while (isListening){
            try {
                semaphore.acquire();
                connectionSocket = serverSocket.accept();
                threadPool.execute(() -> handleRequest(connectionSocket));
            } catch (Exception e){
                log.warn("Error during of handling client request. Cause: " + e.getMessage());
            } finally {
                semaphore.release();
            }
        }
        threadPool.shutdown();
    }

    private void handleRequest(Socket connectionSocket){
        try {
            try {
                in = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                out = new BufferedWriter(new OutputStreamWriter(connectionSocket.getOutputStream()));
                String test = in.readLine();
                out.write(test + "\n");
                out.flush();
            } finally {
                connectionSocket.close();
                in.close();
                out.close();
            }
        } catch (IOException e) {
            log.error("Response was not sent to client. Cause:" + e.getMessage());
        }
    }


    @Override
    public void stopServer() throws IOException {
        isListening = false;
        serverSocket.close();
    }
}
