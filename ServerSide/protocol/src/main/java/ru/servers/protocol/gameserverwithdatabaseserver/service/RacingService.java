package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.Racing;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.User;

import java.util.List;

public interface RacingService {

    boolean addNewRacing(Racing newRacing);

    boolean removeRacingById(int id);

    Racing getRacingByID(int id);

    List<Racing> getAllRacings();

}
