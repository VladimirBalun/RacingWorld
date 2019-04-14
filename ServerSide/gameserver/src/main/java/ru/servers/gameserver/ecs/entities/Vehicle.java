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

import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;
import ru.servers.gameserver.ecs.components.Component;
import ru.servers.gameserver.ecs.components.ComponentType;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

@ToString
@EqualsAndHashCode
@NoArgsConstructor
public class Vehicle implements Entity{

    private Map<ComponentType, Component> components = new HashMap<>();

    @Override
    public void addComponent(ComponentType componentType, Component component) {
        components.put(componentType, component);
    }

    @Override
    public Component getComponent(ComponentType componentType) {
        return components.get(componentType);
    }

    @Override
    public Iterator<Map.Entry<ComponentType, Component>> getComponents() {
        return components.entrySet().iterator();
    }

    @Override
    public int getCountComponents() {
        return components.size();
    }

    @Override
    public void removeComponent(ComponentType componentType) {
        components.remove(componentType);
    }

}
