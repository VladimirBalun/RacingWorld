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

package ru.servers.authorizationServer.network.protocol;

import java.nio.charset.StandardCharsets;

public class AuthorizationRequest {

    // Byte protocol from client
    // [0...253] - email address
    // [254..286] - username
    // [287...319] - password

    private byte[] bufferFromRequest;

    public static final int SIZE_REQUEST = 320;
    public static final int MAX_SIZE_EMAIL = 254;
    public static final int MAX_SIZE_USERNAME = 32;
    public static final int MAX_SIZE_PASSWORD = 32;

    public AuthorizationRequest(byte[] bufferFromRequest){
        if (bufferFromRequest == null) {
            throw new IllegalArgumentException("Incorrect buffer from client. Buffer is null");
        }

        if (bufferFromRequest.length == SIZE_REQUEST) {
            this.bufferFromRequest = bufferFromRequest;
        } else {
            throw new IllegalArgumentException("Incorrect buffer from client. Size of buffer: " + bufferFromRequest.length);
        }
    }

    public byte[] getBuffer(){
        return bufferFromRequest;
    }

    public String getEmail() {
        // [0...253]  - email address
        return new String(bufferFromRequest, 0, 254, StandardCharsets.UTF_8);
    }

    public String getUserName() {
        // [254..286] - username
        return new String(bufferFromRequest, 254, 32, StandardCharsets.UTF_8);
    }

    public String getPassword() {
        // [287...319] - password
        return new String(bufferFromRequest, 287, 32, StandardCharsets.UTF_8);
    }

}
