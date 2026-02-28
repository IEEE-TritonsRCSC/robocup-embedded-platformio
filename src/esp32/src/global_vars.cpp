#include "global_vars.h"

WiFiUDP UDP;
IPAddress multicastIP(239, 42, 42, 42);

HardwareSerial robotSerial(2);

std::array<uint8_t, MOTOR_CMD_HEADER_SIZE> motor_cmd_headers = {0xCA, 0xFE};

PacketInfo packet_info;
CommsBuffer commsBuffer;
MotionCommand current_cmd(0.0f, 0.0f, 0.0f);
KickerState kicker_state;

bool stop_dribbler_on_next_command = false;

float wheel_velocities[NUM_WHEELS] = {0.0f, 0.0f, 0.0f, 0.0f};