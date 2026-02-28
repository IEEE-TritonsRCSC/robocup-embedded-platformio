#include "executors.h"
#include "helpers.h"
#include "global_vars.h"
#include "hardwareControllers.h"

void execute_stop(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    PRINT("Stopping | ");
    robotVelocity.vel_u = 0.0f;
    robotVelocity.vel_v = 0.0f;
    robotVelocity.vel_w = 0.0f;
    setDribbler(false,motor_command);
    prepare_and_send_motor_command(robotVelocity, motor_command);
}

void execute_turn(float angular_speed, RobotVelocity &robotVelocity)
{
    PRINT("Turning at ", angular_speed, " rad/s | ");
    robotVelocity.vel_w = angular_speed;
}

void execute_dash(float power, float dir, RobotVelocity &robotVelocity)
{
    PRINT("Dashing with ", power, " power in ", dir, " radians | ");
    float acceleration = 0.006 * power;
    robotVelocity.vel_u += acceleration * sinf(dir);
    robotVelocity.vel_v += acceleration * cosf(dir);
    robotVelocity.vel_w = 0.0f;
}

void execute_skick(float power, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    PRINT("Short Kicking the ball with ", power, " power | ");
    bool dribbler_on = (power > 0.0f);
    setDribbler(dribbler_on,motor_command);
    stop_dribbler_on_next_command = dribbler_on;
    robotVelocity.vel_w = 0.0f;
}

void execute_kick(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    PRINT("Kicking the ball | ");
    setDribbler(false,motor_command);
    if (kicker_state.kicker_charged)
    {
        kicker_state.kicker_charged = false;
        digitalWrite(KICKER_PIN, HIGH); // turn ON the kicker
        kicker_state.last_kick_time = millis();
        PRINT(" Kicker fired! | ");
    }
    robotVelocity.vel_w = 0.0f;
}

void execute_catch(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    PRINT("Catching the ball | ");
    setDribbler(true,motor_command);
    robotVelocity.vel_w = 0.0f;
}
