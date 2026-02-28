#pragma once

#include "WiFi.h"
#include "global_consts.h"
#include "PacketInfo.h"
#include "KickerState.h"
#include "CommsBuffer.h"
#include "RobotVelocity.h"
#include "MotionCommand.h"

extern WiFiUDP UDP;
extern IPAddress multicastIP;

extern std::array<uint8_t, MOTOR_CMD_HEADER_SIZE> motor_cmd_headers;

extern PacketInfo packet_info;
extern KickerState kicker_state;
extern CommsBuffer commsBuffer;
extern HardwareSerial robotSerial;
extern MotionCommand current_cmd;

extern bool stop_dribbler_on_next_command;

extern float wheel_velocities[NUM_WHEELS];