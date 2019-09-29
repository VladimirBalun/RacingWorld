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

import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.ToString;
import ru.servers.gameserver.ecs.components.Component;
import ru.servers.gameserver.ecs.components.ComponentType;

import java.util.Iterator;
import java.util.Map;

@AllArgsConstructor
@Getter
@ToString
@EqualsAndHashCode
public abstract class Entity {

    private Map<ComponentType, Component> components;

    protected boolean componentTypeIsCorrect(ComponentType componentType, Component component) {
        return componentType.getComponentClass().equals(component.getClass());
    }

    public abstract void addComponent(ComponentType componentType, Component component);

    public abstract Component getComponent(ComponentType componentType);

    public abstract Iterator<Map.Entry<ComponentType, Component>> getIteratorComponents();

    public abstract int getCountComponents();

    public abstract void removeComponent(ComponentType componentType);

}
