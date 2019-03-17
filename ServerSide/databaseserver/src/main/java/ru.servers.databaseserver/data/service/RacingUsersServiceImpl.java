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
import ru.servers.databaseserver.data.dao.RacingUsersRepository;
import ru.servers.databaseserver.data.dao.RacingUsersRepositoryImpl;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.RacingUser;
import ru.servers.protocol.gameserverwithdatabaseserver.service.RacingUsersService;

@Log4j
public class RacingUsersServiceImpl implements RacingUsersService {

    private RacingUsersRepository racingUsersRepository = new RacingUsersRepositoryImpl();

    @Override
    public boolean addNewRacingUser(RacingUser newRacingUser) {
        boolean addingResult = racingUsersRepository.save(newRacingUser);
        if (addingResult) {
            log.debug("New racingUser was added. RacingUser: " + newRacingUser.toString());
        } else {
            log.warn("RacingUser was not added. RacingUser: " + newRacingUser.toString());
        }
        return addingResult;
    }

    @Override
    public boolean removeRacingUserById(int id) {
        boolean deletingResult = racingUsersRepository.removeById(id);
        if (deletingResult){
            log.debug("RacingUser was deleted by id: " + id);
        } else {
            log.warn("RacingUser was not deleted by id: " + id);
        }
        return deletingResult;
    }
}
