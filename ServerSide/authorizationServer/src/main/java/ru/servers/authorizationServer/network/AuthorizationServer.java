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

package ru.servers.authorizationServer.network;

import lombok.extern.log4j.Log4j;
import ru.servers.authorizationServer.network.protocol.AuthorizationAnswer;
import ru.servers.authorizationServer.network.protocol.AuthorizationRequest;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;

@Log4j
public final class AuthorizationServer implements Server {

    private boolean isListening;
    private ServerSocket serverSocket;

    public AuthorizationServer(int port) throws IOException {
        serverSocket = new ServerSocket(port);
    }

    @Override
    public void startServer(int maxCountConnections) throws InterruptedException, IOException {
        ExecutorService threadPool = Executors.newFixedThreadPool(maxCountConnections);
        Semaphore semaphore = new Semaphore(maxCountConnections);
        log.info("Authorization server was started.");
        isListening = true;

        while (isListening){
            semaphore.acquire();
            Socket clientSocket = serverSocket.accept();
            log.debug("Request came from: " + clientSocket.getRemoteSocketAddress().toString());
            threadPool.execute(() -> {
                try {
                    handleRequest(clientSocket);
                } catch (IOException e) {
                    log.error("Error during working with request. Cause:" + e.getMessage());
                } finally {
                    semaphore.release();
                }
            });
        }
    }

    private void handleRequest(Socket clientSocket) throws IOException {
        InputStream inputStream = clientSocket.getInputStream();
        OutputStream outputStream = clientSocket.getOutputStream();

        try {
            byte[] buffer = new byte[AuthorizationRequest.SIZE_REQUEST];
            inputStream.read(buffer, 0, buffer.length);
            NetworkHandler networkHandler = new AuthorizationHandler();
            AuthorizationRequest authorizationRequest = new AuthorizationRequest(buffer);
            boolean resultHandling = networkHandler.handleRequest(authorizationRequest);
            AuthorizationAnswer authorizationAnswer = new AuthorizationAnswer(resultHandling);
            outputStream.write(authorizationAnswer.getBuffer());
            outputStream.flush();
            log.debug("Request was handled successfully.");
        } catch (Exception e) {
            System.out.println("Error during of handling of request. Cause: " + e.getMessage());
            AuthorizationAnswer authorizationAnswer = new AuthorizationAnswer(false);
            outputStream.write(authorizationAnswer.getBuffer());
            outputStream.flush();
        }
    }

    @Override
    public void stopServer() throws IOException {
        isListening = false;
        serverSocket.close();
    }

}
