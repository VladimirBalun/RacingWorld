package ru.servers.gameserver.math.stereometry;

import ru.servers.gameserver.math.algebra.vectors.Vector3;
import ru.servers.gameserver.math.algebra.vectors.Vectors;
import lombok.Getter;
import lombok.Setter;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.AllArgsConstructor;

@Getter
@Setter
@EqualsAndHashCode
@NoArgsConstructor
@AllArgsConstructor
public class Sphere {

    private double radius;
    private Vector3 centerPoint;

    public double getVolume() { return (4/3) * Math.PI * Math.pow(radius, 3); }

    public boolean isInside(Vector3 point) {
        double lengthBetweenPointAndCircleCenter = Vectors.getLengthBetweenTwoVectors(point, centerPoint);
        return lengthBetweenPointAndCircleCenter < radius;
    }

}