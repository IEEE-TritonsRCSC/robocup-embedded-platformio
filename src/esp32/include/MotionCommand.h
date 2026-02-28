#pragma once
class MotionCommand
{
    public:
    float power;
    float dir;
    float angular_speed;

    MotionCommand(float power, float dir, float angular_speed) : power(power), dir(dir), angular_speed(angular_speed) {}
};