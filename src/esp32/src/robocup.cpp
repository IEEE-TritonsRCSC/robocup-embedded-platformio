#include "global_vars.h"
#include "hardwareControllers.h"
#include "helpers.h"

#define MULTICAST_PORT 11000

#define BAUD_RATE 115200

#define TX_PIN 17
#define RX_PIN 16

void setup() {
  Serial.begin(BAUD_RATE);

  initializeAndBlinkLED(LED_PIN, NUM_BLINK, BLINK_INTERVAL);

  connect_wifi();
  UDP.beginMulticast(multicastIP, MULTICAST_PORT);

  robotSerial.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);

  init_motor_command();

  kicker_state.initializePinsAndChargeKicker();

  PRINT("READY\n");
}

void loop() {
  packet_info.updatePacketSizesAndReadAllPacketsAndProcessLastPacket(UDP, robotVelocity);

  kicker_state.checkAndUpdateKickerStatus();
}
