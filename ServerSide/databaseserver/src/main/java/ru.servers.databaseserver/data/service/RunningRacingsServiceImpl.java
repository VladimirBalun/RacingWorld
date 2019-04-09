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

package ru.servers.databaseserver.data.service;

import lombok.extern.log4j.Log4j;
import ru.servers.databaseserver.data.dao.MapsRepository;
import ru.servers.databaseserver.data.dao.MapsRepositoryImpl;
import ru.servers.databaseserver.data.dao.PlayingUsersRepository;
import ru.servers.databaseserver.data.dao.RunningRacesRepository;
import ru.servers.databaseserver.data.dao.RunningRacesRepositoryImpl;
import ru.servers.databaseserver.data.dao.PlayingUsersRepositoryImpl;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.Map;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.PlayingUser;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.User;
import ru.servers.protocol.gameserverwithdatabaseserver.service.RunningRacingsService;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;
import java.util.List;

@Log4j
public class RunningRacingsServiceImpl extends UnicastRemoteObject implements RunningRacingsService {

    private static final long serialVersionUID = 46395104933680006L;

    private MapsRepository mapsRepository = new MapsRepositoryImpl();
    private RunningRacesRepository runningRacesRepository = new RunningRacesRepositoryImpl();
    private PlayingUsersRepository playingUsersRepository = new PlayingUsersRepositoryImpl();

    public RunningRacingsServiceImpl() throws RemoteException {
        super();
    }

    @Override
    public boolean startRacing(String mapName) throws RemoteException {
        Map map = mapsRepository.findByName(mapName);
        RunningRaces newRunningRaces = new RunningRaces(new Date(), map);
        boolean startResult = runningRacesRepository.save(newRunningRaces);
        if (startResult){
            log.debug("Racing was started. Racing map: " + mapName + " Start time: " + new Date().toString());
        } else {
            log.warn("Racing was not started. Racing map: " + mapName);
        }
        return startResult;
    }

    @Override
    public boolean addUserToRacing(int racingID, User user) throws RemoteException {
        RunningRaces runningRaces = runningRacesRepository.findById(racingID);
        PlayingUser playingUser = new PlayingUser(user, runningRaces);
        boolean addingResult = playingUsersRepository.save(playingUser);
        if (addingResult){
            log.debug("User was added to race. User: " + user.toString() + " racing id: " + racingID);
        } else {
            log.debug("User was not added to race. User: " + user.toString() + " racing id: " + racingID);
        }
        return addingResult;
    }

    @Override
    public boolean removeUserFromRacingByID(int userID) throws RemoteException {
        boolean deletingResult = playingUsersRepository.removeUserByUserId(userID);
        if (deletingResult){
            log.debug("User was deleted by user id. User id: " + userID);
        } else {
            log.warn("User was not deleted by user id. User id: " + userID);
        }
        return deletingResult;
    }

    @Override
    public boolean stopRacingByID(int id) throws RemoteException {
        boolean stopResult = runningRacesRepository.removeById(id);
        if (stopResult){
            log.debug("Racing was stopped. id racing: " + id);
        } else {
            log.warn("Racing was not stopped. id racing: " + id);
        }
        return stopResult;
    }

    @Override
    public RunningRaces getRunningRacingByID(int id) throws RemoteException {
        RunningRaces runningRaces = runningRacesRepository.findById(id);
        if (runningRaces == null){
            log.warn("Running racing was not find by id. Id: " + id);
        }
        return runningRaces;
    }

    @Override
    public List<RunningRaces> getAllRunningRacing() throws RemoteException {
        List<RunningRaces> runningRaces = runningRacesRepository.getAllRacings();
        if (runningRaces == null){
            log.warn("There is no active race");
        }
        return runningRaces;
    }

}
