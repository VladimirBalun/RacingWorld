package ru.servers.gameserver.math.algebra.matrices;

import ru.servers.gameserver.math.CoordinateAxis;
import ru.servers.gameserver.math.algebra.vectors.Vector3;

public final class MatricesUtil {

    private MatricesUtil() {
        throw new UnsupportedOperationException("instance for class MatricesUtil can not be created");
    }

    public static Matrix2x2 getIdentity2x2(){
        return new Matrix2x2(new double[] {
                1.0, 0.0,
                0.0, 1.0
        });
    }

    public static Matrix3x3 getIdentity3x3(){
        return new Matrix3x3(new double[] {
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
        });
    }

    public static Matrix4x4 getIdentity4x4(){
        return new Matrix4x4(new double[] {
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
        });
    }

    public static Matrix2x2 getRotation2x2(double angle){
        return new Matrix2x2(new double[] {
                Math.cos(angle), -Math.sin(angle),
                Math.sin(angle), Math.cos(angle)
        });
    }

    public static Matrix3x3 getRotation3x3(double angle, CoordinateAxis axis) throws IllegalArgumentException{
        switch (axis){
            case X_AXIS:
                return new Matrix3x3(new double[] {
                        1.0, 0.0, 0.0,
                        0.0, Math.cos(angle), -Math.sin(angle),
                        0.0, Math.sin(angle), Math.cos(angle),
                });
            case Y_AXIS:
                return new Matrix3x3(new double[] {
                        Math.cos(angle), 0.0, -Math.sin(angle),
                        0.0, 1.0, 0.0,
                        Math.sin(angle), 0.0, Math.cos(angle)
                });
            case Z_AXIS:
                return new Matrix3x3(new double[] {
                        Math.cos(angle), -Math.sin(angle), 0.0,
                        Math.sin(angle), 1.0, Math.cos(angle),
                        0.0, 0.0, 1.0
                });
            default:
                throw new IllegalArgumentException("Incorrect axis for rotation matrix.");
        }
    }

    public static Matrix4x4 getRotation(double angle, CoordinateAxis axis) throws IllegalArgumentException {
        switch (axis) {
            case X_AXIS:
                return new Matrix4x4(new double[]{
                        1.0, 0.0, 0.0, 0.0,
                        0.0, Math.cos(angle), -Math.sin(angle), 0.0,
                        0.0, Math.sin(angle), Math.cos(angle), 0.0,
                        0.0, 0.0, 0.0, 1.0
                });
            case Y_AXIS:
                return new Matrix4x4(new double[]{
                        Math.cos(angle), 0.0, -Math.sin(angle), 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        Math.sin(angle), 0.0, Math.cos(angle), 0.0,
                        0.0, 0.0, 0.0, 1.0
                });
            case Z_AXIS:
                return new Matrix4x4(new double[]{
                        Math.cos(angle), -Math.sin(angle), 0.0, 0.0,
                        Math.sin(angle), 1.0, Math.cos(angle), 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0
                });
            default:
                throw new IllegalArgumentException("Incorrect axis for rotation matrix.");
        }
    }

    public static Matrix4x4 getTranslation(Vector3 vector){
        return new Matrix4x4(new double[] {
                1.0, 0.0, 0.0, vector.getX(),
                0.0, 1.0, 0.0, vector.getY(),
                0.0, 0.0, 1.0, vector.getZ(),
                0.0, 0.0, 0.0, 1.0
        });
    }

    public static Matrix4x4 getScale(Vector3 vector){
        return new Matrix4x4(new double[] {
                vector.getX(), 0.0, 0.0, 0.0,
                0.0, vector.getY(), 0.0, 0.0,
                0.0, 0.0, vector.getZ(), 0.0,
                0.0, 0.0, 0.0, 1.0
        });
    }
}