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

import ru.servers.gameserver.ecs.components.*;

import java.util.HashMap;
import java.util.Map;

public class ComponentManagerImpl implements ComponentManager {

    private Map<ComponentType, Component> components = new HashMap<>();

    public ComponentManagerImpl() {
        components.put(ComponentType.MASS_COMPONENT, new Mass());
        components.put(ComponentType.HEALTH_COMPONENT, new Health());
        components.put(ComponentType.LOCATION_COMPONENT, new Location());
        components.put(ComponentType.DIRECTION_COMPONENT, new Direction());
        components.put(ComponentType.SPEED_COMPONENT, new Speed());
    }

    @Override
    public Component getComponent(ComponentType componentType) {
        return components.get(componentType).clone();
    }

}
