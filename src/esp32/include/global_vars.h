#pragma once

#include "WiFi.h"
#include "global_consts.h"
#include "PacketInfo.h"
#include "CommsBuffer.h"

extern WiFiUDP UDP;

extern PacketInfo packet_info;
extern CommsBuffer commsBuffer;

extern float wheel_velocities[NUM_WHEELS];