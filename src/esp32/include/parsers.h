#pragma once

#define RELEVANT_FORMAT ROBOT_NO " %s %n"
#define ROBOT_NO "1"

void handleNewChar(char c);
void parseMsg(char *msg);
void parseCommand(char *command, char *parameters);