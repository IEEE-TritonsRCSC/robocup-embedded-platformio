#pragma once

#include "RobotVelocity.h"

#define LED_PIN 2
#define LED_ON HIGH
#define LED_OFF LOW
#define NUM_BLINK 4
#define BLINK_INTERVAL 100

#define DRIBBLER_ON 0x01
#define DRIBBLER_OFF 0x00
#define DRIBBLER_MOTOR_INDEX 10

#define FRONT_ANGLE 30              // angle of front wheels (deg)
#define BACK_ANGLE 60               // angle of back wheels (deg)
#define rad_robot 0.086F            // robot radius (m) (from center to wheel contact point)
#define rad_wheel 0.025F            // wheel radius (m)
#define MOTOR_REDUCTION_RATIO 36.0F // motor:wheel ratio
#define RADS_TO_RPM 9.549296F       // 60 / (2*pi)

#define cosFront (float) cosf(FRONT_ANGLE * M_PI / 180)
#define sinFront (float) sinf(FRONT_ANGLE * M_PI / 180)
#define cosBack (float) cosf(BACK_ANGLE * M_PI / 180)
#define sinBack (float) sinf(BACK_ANGLE * M_PI / 180)

void blink(int led, int count, int interval);
void initializeAndBlinkLED(int led, int count, int interval);
void setDribbler(bool on);
void prepare_and_send_motor_command();
void connect_wifi();
void init_motor_command();
void sendMotorCommand();
void translateVelUandVelVIntoWheelVelocities(float wheel_velocities[4], RobotVelocity &robotVelocity);
void decayVelUandVelV(RobotVelocity &robotVelocity);
void translateWheelVelocitiesIntoAngular(float wheel_velocities[4], int wheelIndex);
void addAngularVelocitiesToWheelVelocities(float wheel_velocities[4], RobotVelocity &robotVelocity, int wheelIndex);
void waitUntilWiFiConnected(int waitInterval);
void printWiFiConnectingMessage();
void printWiFiConnectedMessage();
void beginWiFiAndWait(int waitInterval);
void turnLEDOn(int led);
void turnLEDOff(int led);