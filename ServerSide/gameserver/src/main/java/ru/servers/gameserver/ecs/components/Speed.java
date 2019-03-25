package ru.servers.gameserver.ecs.components;

import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.ToString;

@Getter
@ToString
@EqualsAndHashCode
public class Speed implements Component {

    private final double MIN_SPEED;
    private final double MAX_SPEED;
    private double speed;
    private double acceleration;

    public Speed(double MIN_SPEED, double MAX_SPEED, double speed, double acceleration) {
        this.MIN_SPEED = MIN_SPEED;
        this.MAX_SPEED = MAX_SPEED;
        if (speed < MIN_SPEED) {
            this.speed = MIN_SPEED;
        }
        if (speed > MAX_SPEED) {
            this.speed = MAX_SPEED;
        }
        this.acceleration = acceleration;
    }

    @Override
    public Component clone() {
        try {
            return (Speed) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new InternalError();
        }
    }

    public void setSpeed(double speed) {
        if (speed < MIN_SPEED) {
            this.speed = MIN_SPEED;
        }
        if (speed > MAX_SPEED) {
            this.speed = MAX_SPEED;
        }
    }

    public void setAcceleration(double acceleration) {
        this.acceleration = acceleration;
    }
}
