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
import ru.servers.databaseserver.data.dao.RunningRacesRepository;
import ru.servers.databaseserver.data.dao.RunningRacesRepositoryImpl;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;
import ru.servers.protocol.gameserverwithdatabaseserver.service.RunningRacesService;

@Log4j
public class RunningRacesServiceImpl implements RunningRacesService {

    private RunningRacesRepository runningRacesRepository = new RunningRacesRepositoryImpl();

    @Override
    public boolean addNewRunningRaces(RunningRaces newRunningRaces) {
        boolean addingResult = runningRacesRepository.save(newRunningRaces);
        if (addingResult) {
            log.debug("New RunningRaces was added. RunningRaces: " + newRunningRaces.toString());
        } else {
            log.warn("RunningRaces was not added. RunningRaces: " + newRunningRaces.toString());
        }
        return addingResult;
    }

    @Override
    public boolean removeRunningRacesById(int id) {
        boolean deletingResult = runningRacesRepository.removeById(id);
        if (deletingResult){
            log.debug("RunningRaces was deleted by id: " + id);
        } else {
            log.warn("RunningRaces was not deleted by id: " + id);
        }
        return deletingResult;
    }
}
