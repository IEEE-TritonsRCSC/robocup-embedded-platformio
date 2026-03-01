#pragma once

#include "WiFi.h"
#include "global_consts.h"
#include "PacketInfo.h"
#include "KickerState.h"
#include "CommsBuffer.h"
#include "RobotVelocity.h"
#include "MotionCommand.h"

extern WiFiUDP UDP;

extern PacketInfo packet_info;
extern CommsBuffer commsBuffer;
extern MotionCommand current_cmd;

extern float wheel_velocities[NUM_WHEELS];