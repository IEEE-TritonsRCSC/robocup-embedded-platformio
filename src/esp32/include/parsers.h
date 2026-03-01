#pragma once

#include "RobotVelocity.h"
#include "KickerState.h"
#include "HardwareSerial.h"
#include "global_consts.h"

#define RELEVANT_FORMAT ROBOT_NO " %s %n"
#define ROBOT_NO "1"

void handleNewChar(char c, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial);
void parseMsg(char *msg, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial);
void parseCommand(char *command, char *parameters, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial);