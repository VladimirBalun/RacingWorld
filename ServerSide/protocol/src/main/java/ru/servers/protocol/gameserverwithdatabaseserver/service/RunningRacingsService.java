package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.User;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface RunningRacingsService extends Remote {

    boolean startRacing(String mapName) throws RemoteException;

    boolean addUserToRacing(int racingID, User user) throws RemoteException;

    boolean removeUserFromRacingByID(int userID) throws RemoteException;

    boolean stopRacingByID(int id) throws RemoteException;

    RunningRaces getRunningRacingByID(int id) throws RemoteException;

    List<RunningRaces> getAllRunningRacing() throws RemoteException;

}
