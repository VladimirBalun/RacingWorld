package ru.servers.gameserver.ecs.components;

import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.ToString;

@Getter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
public class Speed implements Component {

    private double minSpeed;
    private double maxSpeed;
    private double speed;
    private double acceleration;

    public Speed(double minSpeed, double maxSpeed, double speed, double acceleration) {
        this.minSpeed = minSpeed;
        this.maxSpeed = maxSpeed;
        setSpeed(speed);
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
        if (speed < minSpeed) {
            this.speed = minSpeed;
        }
        if (speed > maxSpeed) {
            this.speed = maxSpeed;
        }
    }

    public void setAcceleration(double acceleration) {
        this.acceleration = acceleration;
    }
}
