#pragma once

#include "RobotVelocity.h"
#include "global_consts.h"

void execute_stop(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command);
void execute_turn(float angular_speed, RobotVelocity &robotVelocity);
void execute_dash(float power, float dir, RobotVelocity &robotVelocity);
void execute_skick(float power, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command);
void execute_kick(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command);
void execute_catch(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command);
