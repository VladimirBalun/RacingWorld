package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.Racing;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface RacingService extends Remote {

    boolean addNewRacing(Racing newRacing) throws RemoteException;

    boolean removeRacingById(int id) throws RemoteException;

    Racing getRacingByID(int id) throws RemoteException;

    List<Racing> getAllRacings() throws RemoteException;

}
