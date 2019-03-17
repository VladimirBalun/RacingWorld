/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package ru.servers.databaseserver.data.service;

import lombok.extern.log4j.Log4j;
import ru.servers.databaseserver.data.dao.PlayingUsersRepository;
import ru.servers.databaseserver.data.dao.PlayingUsersRepositoryImpl;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.PlayingUser;
import ru.servers.protocol.gameserverwithdatabaseserver.service.PlayingUsersService;

@Log4j
public class PlayingUsersServiceImpl implements PlayingUsersService {
    private PlayingUsersRepository playingUsersRepository = new PlayingUsersRepositoryImpl();

    @Override
    public boolean addNewPlayingUser(PlayingUser newPlayingUser) {
        boolean addingResult = playingUsersRepository.save(newPlayingUser);
        if (addingResult) {
            log.debug("New playingUser was added. PlayingUser: " + newPlayingUser.toString());
        } else {
            log.warn("PlayingUser was not added. PlayingUser: " + newPlayingUser.toString());
        }
        return addingResult;
    }

    @Override
    public boolean removePlayingUserById(int id) {
        boolean deletingResult = playingUsersRepository.removeById(id);
        if (deletingResult){
            log.debug("PlayingUser was deleted by id: " + id);
        } else {
            log.warn("PlayingUser was not deleted by id: "  + id);
        }
        return deletingResult;
    }
}
