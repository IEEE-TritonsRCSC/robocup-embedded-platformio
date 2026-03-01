#pragma once
class MotionCommand
{
    public:
    float power;
    float dir;
    float angular_speed;

    /**
     * Creates a motion command with the provided parameters.
     * @param power Translational power.
     * @param dir Direction of motion.
     * @param angular_speed Angular speed.
     */
    MotionCommand(float power, float dir, float angular_speed) : power(power), dir(dir), angular_speed(angular_speed) {}
};
