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

package ru.servers.authorizationServer;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import ru.servers.authorizationServer.network.protocol.AuthorizationRequest;

public class AuthorizationRequestTest {

    private String testEmail = "tester@gmail.com";
    private String testUsername = "tester";
    private String testPassword = "12345";

    // Byte protocol from client
    // [0...253] - email address
    // [254..286] - username
    // [287...319] - password

    private byte[] byteBuffer = new byte[AuthorizationRequest.SIZE_REQUEST];
    private AuthorizationRequest request = new AuthorizationRequest(byteBuffer);

    @Before
    public void initializeCorrectBuffer(){
        // [0...253] - email address
        for (int i = 0; i < testEmail.length(); i++) {
            byteBuffer[i] = (byte) testEmail.charAt(i);
        }
        // [254..286] - username
        for (int i = 0; i < testUsername.length(); i++) {
            byteBuffer[254 + i] = (byte) testUsername.charAt(i);
        }
        // [287...319] - password
        for (int i = 0; i < testPassword.length(); i++) {
            byteBuffer[287 + i] = (byte) testPassword.charAt(i);
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void initializationOfBufferToNull(){
        new AuthorizationRequest(null);
    }

    @Test(expected = IllegalArgumentException.class)
    public void initializationOfBufferLessThanBufferSize(){
        byte[] incorrectBuffer = new byte[AuthorizationRequest.SIZE_REQUEST - 10];
        new AuthorizationRequest(incorrectBuffer);
    }

    @Test(expected = IllegalArgumentException.class)
    public void initializingBufferMoreThanBufferSize(){
        byte[] incorrectBuffer = new byte[AuthorizationRequest.SIZE_REQUEST + 10];
        new AuthorizationRequest(incorrectBuffer);
    }

    @Test
    public void gettingEmailFromAuthorizationRequest(){
        Assert.assertEquals(testEmail, request.getEmail());
    }

    @Test
    public void gettingUsernameFromAuthorizationRequest(){
        Assert.assertEquals(testUsername, request.getUserName());
    }

    @Test
    public void gettingPasswordFromAuthorizationRequest(){
        Assert.assertEquals(testPassword, request.getPassword());
    }

}
