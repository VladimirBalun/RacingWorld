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

import lombok.extern.log4j.Log4j;
import ru.servers.gameserver.ecs.components.ComponentType;
import ru.servers.gameserver.ecs.components.Health;
import ru.servers.gameserver.ecs.components.Location;
import ru.servers.gameserver.ecs.entities.Entity;
import ru.servers.gameserver.ecs.entities.EntityType;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

@Log4j
public class ECSGameSystem implements ECS {

    private final byte MAX_COUNT_PLAYERS = 10;

    private EntityManager entityManager = new EntityManagerImpl();
    private ComponentManager componentManager = new ComponentManagerImpl();

    @Override
    public synchronized int createPlayer(Vector3 position, Vector3 direction) {
        if (entityManager.getCountEntities() == MAX_COUNT_PLAYERS) {
            return 0;
        }

        int token = entityManager.createEntity(EntityType.VEHICLE_ENTITY);
        Entity createdEntity = entityManager.getEntity(token);
        Health health = (Health) componentManager.getComponent(ComponentType.HEALTH_COMPONENT);
        Location location = (Location) componentManager.getComponent(ComponentType.LOCATION_COMPONENT);
        createdEntity.addComponent(ComponentType.HEALTH_COMPONENT, health);
        createdEntity.addComponent(ComponentType.LOCATION_COMPONENT, location);
        return token;
    }

    @Override
    public synchronized int getCountPlayers() {
        return entityManager.getCountEntities();
    }

    @Override
    public synchronized boolean removePlayer(int token) {
        return entityManager.destroyEntity(token);
    }

    @Override
    public synchronized Location getPlayerLocation(int token) {
        return (Location) entityManager.getEntity(token).getComponent(ComponentType.LOCATION_COMPONENT);
    }

}
