package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;

public interface RunningRacesService {

    boolean addNewRunningRaces(RunningRaces newRunningRaces);

    boolean removeRunningRacesById(int id);
}
