#pragma once
class RobotVelocity {
private:
    float vel_u;
    float vel_v;
    float vel_w;

public:
    RobotVelocity() : vel_u(0.0f), vel_v(0.0f), vel_w(0.0f) {}

    void setAll(float val);
    void setVelU(float val);
    void setVelV(float val);
    void setVelW(float val);

    float getVelU();
    float getVelV();
    float getVelW();

    void incrVelU(float val);
    void incrVelV(float val);

    void multVelU(float mult);
    void multVelV(float mult);
};