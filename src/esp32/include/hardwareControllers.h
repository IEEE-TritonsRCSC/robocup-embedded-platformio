#pragma once

#include "RobotVelocity.h"
#include "global_consts.h"
#include "HardwareSerial.h"
#include "credentials.h"

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

/**
 * Initializes the LED pin and blinks it.
 * @param led GPIO pin for the LED.
 * @param count Number of blinks.
 * @param interval Delay between toggles in milliseconds.
 */
void initializeAndBlinkLED(int led, int count, int interval);
/**
 * Sets the dribbler on or off in the motor command buffer.
 * @param on True to enable the dribbler, false to disable it.
 * @param motor_command Motor command buffer to update.
 */
void setDribbler(bool on, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command);
/**
 * Prepares and sends a motor command, handling dribbler stop scheduling.
 * @param robotVelocity Robot velocity state to use.
 * @param motor_command Motor command buffer to populate.
 * @param robotSerial Serial interface used to send commands.
 * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
 */
void prepare_and_send_motor_command(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, float wheel_velocities[4]);
/**
 * Connects to WiFi using configured credentials.
 */
void connect_wifi();

/**
 * Initializes the motor command buffer with header bytes.
 * @param motor_command Motor command buffer to initialize.
 * @param motor_cmd_headers Header bytes to write.
 */
void init_motor_command(std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, std::array<uint8_t, MOTOR_CMD_HEADER_SIZE> motor_cmd_headers);
/**
 * Sends a motor command over the serial interface.
 * @param robotVelocity Robot velocity state to use.
 * @param motor_command Motor command buffer to send.
 * @param robotSerial Serial interface used to send commands.
 */
void sendMotorCommand(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, HardwareSerial &robotSerial);

/**
 * Translates robot velocity components into wheel velocities.
 * @param wheel_velocities Output array of wheel velocities.
 * @param robotVelocity Robot velocity state to use.
 */
void translateVelUandVelVIntoWheelVelocities(float wheel_velocities[4], RobotVelocity &robotVelocity);
/**
 * Applies decay to translational velocities.
 * @param robotVelocity Robot velocity state to update.
 */
void decayVelUandVelV(RobotVelocity &robotVelocity);
/**
 * Translates wheel velocities into angular values for a wheel index.
 * @param wheel_velocities Wheel velocity array to update.
 * @param wheelIndex Index of the wheel to update.
 */
void translateWheelVelocitiesIntoAngular(float wheel_velocities[4], int wheelIndex);
/**
 * Adds angular velocity contributions to wheel velocities.
 * @param wheel_velocities Wheel velocity array to update.
 * @param robotVelocity Robot velocity state to use.
 * @param wheelIndex Index of the wheel to update.
 */
void addAngularVelocitiesToWheelVelocities(float wheel_velocities[4], RobotVelocity &robotVelocity, int wheelIndex);

/**
 * Blocks until WiFi is connected, waiting between checks.
 * @param waitInterval Delay between checks in milliseconds.
 */
void waitUntilWiFiConnected(int waitInterval);
/**
 * Prints a WiFi connecting status message.
 */
void printWiFiConnectingMessage();
/**
 * Prints a WiFi connected status message.
 */
void printWiFiConnectedMessage();
/**
 * Begins WiFi connection and waits until connected.
 * @param waitInterval Delay between checks in milliseconds.
 */
void beginWiFiAndWait(int waitInterval);

/**
 * Turns an LED on.
 * @param led GPIO pin for the LED.
 */
void turnLEDOn(int led);
/**
 * Turns an LED off.
 * @param led GPIO pin for the LED.
 */
void turnLEDOff(int led);
/**
 * Blinks an LED a fixed number of times.
 * @param led GPIO pin for the LED.
 * @param count Number of blinks.
 * @param interval Delay between toggles in milliseconds.
 */
void blink(int led, int count, int interval);