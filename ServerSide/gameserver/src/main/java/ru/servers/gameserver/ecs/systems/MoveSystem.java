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

package ru.servers.gameserver.ecs.systems;

import ru.servers.gameserver.ecs.components.Component;
import ru.servers.gameserver.ecs.components.ComponentType;
import ru.servers.gameserver.ecs.components.Location;
import ru.servers.gameserver.ecs.components.Speed;
import ru.servers.gameserver.ecs.entities.Entity;
import ru.servers.gameserver.math.algebra.Quaternion;
import ru.servers.gameserver.math.algebra.vectors.Vector3;
import ru.servers.gameserver.math.algebra.vectors.VectorsUtil;

import java.util.Set;
import java.util.stream.Collectors;

public class MoveSystem implements System {

    @Override
    public void execute(long milliseconds) {
        getFilteredEntities()
                .forEach(entity -> {
                    Speed speed = (Speed) entity.getComponent(ComponentType.SPEED_COMPONENT);
                    Location location = (Location) entity.getComponent(ComponentType.LOCATION_COMPONENT);
                    double oldSpeed = speed.getSpeed();
                    speed.setSpeed(speed.getSpeed() + speed.getAcceleration() * milliseconds);
                    Vector3 deltaPositionVector3 = new Vector3(
                            getDistanceByAxis(VectorsUtil.getAngleBetweenVectors(location.getDirection(),
                                    new Vector3(location.getDirection().getX(), 0, 0)), speed, oldSpeed),
                            getDistanceByAxis(VectorsUtil.getAngleBetweenVectors(location.getDirection(),
                                    new Vector3(0, location.getDirection().getY(), 0)), speed, oldSpeed),
                            getDistanceByAxis(VectorsUtil.getAngleBetweenVectors(location.getDirection(),
                                    new Vector3(0, 0, location.getDirection().getZ())), speed, oldSpeed)
                    );
                    Vector3 deltaDirectionVector3 = new Vector3(
                            location.getPosition().getX(),
                            location.getPosition().getY(),
                            location.getPosition().getZ()
                    );
                    deltaDirectionVector3.sub(location.getDirection());
                    deltaPositionVector3 = rotateVector(deltaPositionVector3,
                            VectorsUtil.getAngleBetweenVectors(deltaPositionVector3, deltaDirectionVector3));
                    deltaDirectionVector3.add(deltaPositionVector3);
                    location.getDirection().add(deltaDirectionVector3);
                });
    }

    @Override
    public Set<Entity> getFilteredEntities() {
        return System.entities.stream()
                .filter(entity -> {
                    Component component = entity.getComponent(ComponentType.SPEED_COMPONENT);
                    if (component != null) {
                        return ((Speed) component).getSpeed() != 0;
                    }
                    return false;
                })
                .collect(Collectors.toSet());
    }

    private double getDistanceByAxis(double angleWithSpecifyVector, Speed speed, double oldSpeed) {
        return (Math.pow(Math.cos(angleWithSpecifyVector) * speed.getSpeed(), 2)
                - Math.pow(Math.cos(angleWithSpecifyVector) * oldSpeed, 2))
                / (2 * speed.getAcceleration());
    }

    private Vector3 rotateVector(Vector3 vector3, double angle) {
        Quaternion quaternion = new Quaternion(Math.cos(angle / 2), vector3);
        Vector3 reversedVector3 = new Vector3(vector3.getX(), vector3.getY(), vector3.getZ());
        reversedVector3.mul(-1);
        Quaternion conjugatedQuaternion = new Quaternion(quaternion.getW(), reversedVector3);
        double normal = Math.pow(vector3.getX(), 2) + Math.pow(vector3.getY(), 2) + Math.pow(vector3.getZ(), 2);
        conjugatedQuaternion.mul(1 / normal);
        quaternion.mul(new Quaternion(0, vector3));
        quaternion.mul(conjugatedQuaternion);
        return quaternion.getVector();
    }
}
