package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.RacingUser;

public interface RacingUsersService {

    boolean addNewRacingUser(RacingUser newRacingUser);

    boolean removeRacingUserById(int id);
}
