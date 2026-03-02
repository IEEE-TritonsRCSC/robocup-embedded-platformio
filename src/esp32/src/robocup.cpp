#include "WiFi.h"
#include "PacketInfo.h"
#include "hardwareControllers.h"
#include "printers.h"

#define MULTICAST_PORT 11000

#define BAUD_RATE 115200

#define TX_PIN 17
#define RX_PIN 16

WiFiUDP UDP;
IPAddress multicastIP(239, 42, 42, 42);

RobotVelocity robotVelocity;
std::array<uint8_t, MOTOR_COMMAND_SIZE> motor_command;
std::array<uint8_t, MOTOR_CMD_HEADER_SIZE> motor_cmd_headers = {0xCA, 0xFE};
KickerState kicker_state;
HardwareSerial robotSerial(2);
bool stop_dribbler_on_next_command = false;
MotionCommand current_cmd(0.0f, 0.0f, 0.0f);
float wheel_velocities[NUM_WHEELS] = {0.0f, 0.0f, 0.0f, 0.0f};
CommsBuffer commsBuffer;
PacketInfo packet_info;

void setup() {
  Serial.begin(BAUD_RATE);

  initializeAndBlinkLED(LED_PIN, NUM_BLINK, BLINK_INTERVAL);

  connectWiFiAndBlink(LED_PIN,NUM_WIFI_BLINK,WIFI_BLINK_INTERVAL);
  UDP.beginMulticast(multicastIP, MULTICAST_PORT);

  robotSerial.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);

  init_motor_command(motor_command, motor_cmd_headers);

  kicker_state.initializePinsAndChargeKicker();

  PRINT("READY\n");
}

void loop() {
  packet_info.updatePacketSizesAndReadAllPacketsAndProcessLastPacket(UDP, robotVelocity, motor_command, kicker_state, robotSerial, stop_dribbler_on_next_command, current_cmd, wheel_velocities, commsBuffer);

  kicker_state.checkAndUpdateKickerStatus();
}
