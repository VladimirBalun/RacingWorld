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

package ru.servers.gameserver.ecs.entities;

import ru.servers.gameserver.ecs.components.Component;
import ru.servers.gameserver.ecs.components.ComponentType;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Vehicle extends Entity {

    public Vehicle() {
        super(new HashMap<>());
    }

    @Override
    public void addComponent(ComponentType componentType, Component component) {
        if (componentTypeIsCorrect(componentType, component)) {
            getComponents().put(componentType, component);
        }
    }

    @Override
    public Component getComponent(ComponentType componentType) {
        return getComponents().get(componentType);
    }

    @Override
    public Iterator<Map.Entry<ComponentType, Component>> getIteratorComponents() {
        return getComponents().entrySet().iterator();
    }

    @Override
    public int getCountComponents() {
        return getComponents().size();
    }

    @Override
    public void removeComponent(ComponentType componentType) {
        getComponents().remove(componentType);
    }

}
