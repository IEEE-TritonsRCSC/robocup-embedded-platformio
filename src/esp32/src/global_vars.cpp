#include "global_vars.h"

WiFiUDP UDP;


PacketInfo packet_info;
CommsBuffer commsBuffer;
MotionCommand current_cmd(0.0f, 0.0f, 0.0f);

float wheel_velocities[NUM_WHEELS] = {0.0f, 0.0f, 0.0f, 0.0f};