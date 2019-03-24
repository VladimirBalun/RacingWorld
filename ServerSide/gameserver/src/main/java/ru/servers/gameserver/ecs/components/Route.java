package ru.servers.gameserver.ecs.components;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import ru.servers.gameserver.math.algebra.vectors.Vector3;


@Getter
@Setter
@NoArgsConstructor
public class Route {

    private Vector3 route;

    @Override
    public Route clone() {
        try {
            return (Route)super.clone();
        }
        catch (CloneNotSupportedException e) {
            throw new InternalError();
        }
    }

}
