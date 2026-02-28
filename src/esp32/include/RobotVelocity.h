#pragma once
class RobotVelocity
{
    public:

    float vel_u;
    float vel_v;
    float vel_w;

    RobotVelocity() : vel_u(0.0f), vel_v(0.0f), vel_w(0.0f) {}
};