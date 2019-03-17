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
import ru.servers.databaseserver.data.dao.MapsRepository;
import ru.servers.databaseserver.data.dao.MapsRepositoryImpl;
import ru.servers.protocol.gameserverwithdatabaseserver.entity.Map;
import ru.servers.protocol.gameserverwithdatabaseserver.service.MapsService;

@Log4j
public class MapsServiceImpl implements MapsService {

    private MapsRepository mapsRepository = new MapsRepositoryImpl();

    @Override
    public boolean addNewMap(Map newMap) {
        boolean addingResult = mapsRepository.save(newMap);
        if (addingResult) {
            log.debug("New map was added. Map: " + newMap.toString());
        } else {
            log.warn("Map was not added. Map: " + newMap.toString());
        }
        return addingResult;
    }

    @Override
    public boolean removeMapByName(String name) {
        boolean deletingResult = mapsRepository.removeByName(name);
        if (deletingResult){
            log.debug("Map was deleted by name: " + name);
        } else {
            log.warn("Map was not deleted by name: " + name);
        }
        return deletingResult;
    }

    @Override
    public boolean renameMapById(int id, String newName) {
        Map map = mapsRepository.findById(id);
        if (map == null){
            log.warn("Map not found by id. Id: " + id);
            return false;
        }
        map.setName(newName);
        log.debug("Id for map with id: '" + id + "' was changed on '" + newName + "'");
        return mapsRepository.updateNameById(id, map);
    }
}
