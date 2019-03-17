package ru.servers.protocol.gameserverwithdatabaseserver.service;

import ru.servers.protocol.gameserverwithdatabaseserver.entity.PlayingUser;

public interface PlayingUsersService {

    boolean addNewPlayingUser(PlayingUser newPlayingUser);

    boolean removePlayingUserById(int id);
}
