package ru.servers.gameserver.math.stereometry;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

public class SphereTest {
    //     _______
    //   /         \
    //   | (0;0;0) |
    //   \ _______ /
    private final double radius = 3.5;
    private final Vector3 centerPoint = new Vector3(0.0, 0.0, 0.0);
    private Sphere sphere = new Sphere(radius, centerPoint);

    @Test // 4/3 * Math.PI * r^3
    public void gettingVolume() {
        double volume = 4/3 * Math.PI * radius * radius * radius;
        Assert.assertEquals(volume, sphere.getVolume(), 0.1);
    }

    @Test
    public void checkingIfPointIsInsideSphere(){
        Assert.assertTrue(sphere.isInside(new Vector3(2.5, 2.0, 0.0)));
    }

}