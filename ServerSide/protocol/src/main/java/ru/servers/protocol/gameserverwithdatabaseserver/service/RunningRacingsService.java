package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.User;

import java.util.List;

public interface RunningRacingsService {

    boolean startRacing(String mapName);

    boolean addUserToRacing(int racingID, User user);

    boolean removeUserFromRacingByID(int userID);

    boolean stopRacingByID(int id);

    RunningRaces getRunningRacingByID(int id);

    List<RunningRaces> getAllRunningRacing();
}
