package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.Map;

public interface MapsService {

    boolean addNewMap(Map newMap);

    boolean removeMapByName(String name);

    boolean renameMapById(int id, String newName);
}
