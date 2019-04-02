package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.Map;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MapsService extends Remote {

    boolean addNewMap(Map newMap) throws RemoteException;

    boolean removeMapByName(String name) throws RemoteException;

    boolean renameMapById(int id, String newName) throws RemoteException;

}
