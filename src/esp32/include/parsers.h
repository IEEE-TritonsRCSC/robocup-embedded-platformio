#pragma once

#include "RobotVelocity.h"

#define RELEVANT_FORMAT ROBOT_NO " %s %n"
#define ROBOT_NO "1"

void handleNewChar(char c, RobotVelocity &robotVelocity);
void parseMsg(char *msg, RobotVelocity &robotVelocity);
void parseCommand(char *command, char *parameters);