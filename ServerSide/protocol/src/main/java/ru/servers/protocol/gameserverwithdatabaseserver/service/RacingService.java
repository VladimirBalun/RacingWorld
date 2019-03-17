package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.Racing;

public interface RacingService {

    boolean addNewRacing(Racing newRacing);

    boolean removeRacingById(int id);

}
