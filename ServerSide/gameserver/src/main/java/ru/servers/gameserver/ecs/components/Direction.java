package ru.servers.gameserver.ecs.components;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class Direction implements Component {

    private Vector3 route;

    @Override
    public Direction clone() {
        try {
            return (Direction)super.clone();
        }
        catch (CloneNotSupportedException e) {
            throw new InternalError();
        }
    }

}
