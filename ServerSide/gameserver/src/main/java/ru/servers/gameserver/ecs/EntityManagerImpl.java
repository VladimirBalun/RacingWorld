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

package ru.servers.gameserver.ecs;

import ru.servers.gameserver.ecs.entities.Vehicle;
import ru.servers.gameserver.ecs.entities.Entity;
import ru.servers.gameserver.ecs.entities.EntityType;

import java.util.HashMap;
import java.util.Map;

public class EntityManagerImpl implements EntityManager {

    private Map<Integer, Entity> entities = new HashMap<>();

    @Override
    public int createEntity(EntityType entityType) {
        switch (entityType) {
            case VEHICLE_ENTITY:
                int entityID = generateEntityID();
                entities.put(entityID, new Vehicle());
                return entityID;
            default:
                return 0;
        }
    }

    @Override
    public Entity getEntity(int entityID) {
        return entities.get(entityID);
    }

    @Override
    public boolean destroyEntity(int entityID) {
        Entity deletedEntity = entities.remove(entityID);
        return deletedEntity != null;
    }

    @Override
    public int getCountEntities() {
        return entities.size();
    }

    private int generateEntityID(){
        if (entities.containsKey(entities.size())) {
            int previousEntityID = -1;
            for (int currentEntityID : entities.keySet()) {
                if (currentEntityID - previousEntityID > 1) {
                    return previousEntityID + 1;
                } else {
                    previousEntityID++;
                }
            }
        }
        return entities.size();
    }

}
