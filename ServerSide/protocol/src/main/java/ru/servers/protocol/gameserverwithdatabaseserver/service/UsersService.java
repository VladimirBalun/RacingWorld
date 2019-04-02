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

package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.Racing;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.User;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface UsersService extends Remote {

    boolean addNewUser(User newUser) throws RemoteException;

    boolean removeUserByEmail(String email) throws RemoteException;

    boolean changeUserPasswordByEmail(String email, String newPassword) throws RemoteException;

    boolean isExist(String email, String password) throws RemoteException;

    List<Racing> getAllRacingsByUserId(int id) throws RemoteException;

}
