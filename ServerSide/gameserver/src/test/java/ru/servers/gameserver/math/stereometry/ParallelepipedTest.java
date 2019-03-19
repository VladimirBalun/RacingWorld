package ru.servers.gameserver.math.stereometry;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

public class ParallelepipedTest {

    private final Vector3 points[] = new Vector3[] {  //         *--------*           Z
            new Vector3(5.0, 0.0, 0.0),      //        /|       /|           |
            new Vector3(0.0, 0.0, 0.0),      //       / |      / |           |
            new Vector3(0.0, 10.0, 0.0),     //      /  |     /  |           |
            new Vector3(5.0, 10.0, 0.0),     //     *--------*   |           |
            new Vector3(5.0, 0.0, 6.0),      //     |   *----|---*           O--------Y
            new Vector3(0.0, 0.0, 6.0),      //     |  /     |  /           /
            new Vector3(0.0, 10.0, 6.0),     //     | /      | /           /
            new Vector3(5.0, 10.0, 6.0)      //     |/       |/           /
    };                                                //     *--------*           X

    private Parallelepiped parallelepiped = new Parallelepiped(points);

    @Test // height * length * width
    public void gettingVolume(){
        final double length = 5.0;
        final double width = 10.0;
        final double height = 6.0;
        final double volume = height * length * width;
        Assert.assertEquals(volume, parallelepiped.getVolume(),1.0);
    }

    @Test // // Test1: Check vertex x in Parallelepiped
    public void checkingVertexOnNonExistingInParallelepiped() {
        Assert.assertFalse(parallelepiped.isInside(new Vector3(-1.0, -1.0, 0.0)));
    }

    @Test // // Test2: Check vertex x in Parallelepiped
    public void checkingVertexOnExistingOnBorderParallelepiped() {
        Assert.assertTrue(parallelepiped.isInside(new Vector3(3.5, 10.0, 0.0)));
    }

    @Test // // Test3: Check vertex x in Parallelepiped
    public void checkingVertexOnExistingInParallelepiped() {
        Assert.assertTrue(parallelepiped.isInside(new Vector3(2.5, 5.0, 3.0)));
    }

}