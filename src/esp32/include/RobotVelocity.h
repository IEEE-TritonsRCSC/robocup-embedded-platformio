#pragma once
class RobotVelocity
{
    public:

    float vel_u;
    float vel_v;
    float vel_w;

    /**
     * Initializes all velocity components to zero.
     */
    RobotVelocity() : vel_u(0.0f), vel_v(0.0f), vel_w(0.0f) {}
};
