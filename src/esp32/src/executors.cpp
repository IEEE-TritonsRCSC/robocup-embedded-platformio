#include "executors.h"
#include "printers.h"
#include "hardwareControllers.h"

void execute_stop(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, float wheel_velocities[4])
{
    printStoppingMessage();
    robotVelocity.setAll(0.0f);
    setDribbler(false,motor_command);
    prepare_and_send_motor_command(robotVelocity, motor_command, robotSerial, stop_dribbler_on_next_command, wheel_velocities);
}

void execute_turn(float angular_speed, RobotVelocity &robotVelocity)
{
    printTurningMessage(angular_speed);
    robotVelocity.setVelW(angular_speed);
}

void execute_dash(float power, float dir, RobotVelocity &robotVelocity)
{
    printDashingMessage(power, dir);
    float acceleration = 0.006 * power;
    robotVelocity.incrVelU(acceleration * sinf(dir));
    robotVelocity.incrVelV(acceleration * cosf(dir));
    robotVelocity.setVelW(0.0f);
}

void execute_skick(float power, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, bool &stop_dribbler_on_next_command)
{
    printShortKickingMessage(power);
    bool dribbler_on = (power > 0.0f);
    setDribbler(dribbler_on,motor_command);
    stop_dribbler_on_next_command = dribbler_on;
    robotVelocity.setVelW(0.0f);
}

void execute_kick(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state)
{
    printKickingMessage();
    setDribbler(false,motor_command);
    if (kicker_state.kicker_charged)
    {
        kicker_state.kicker_charged = false;
        kicker_state.turnOnKicker();
        kicker_state.last_kick_time = millis();
        printKickerFiredMessage();

    }
    robotVelocity.setVelW(0.0f);
}

void execute_catch(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    printCatchingMessage();
    setDribbler(true,motor_command);
    robotVelocity.setVelW(0.0f);
}
