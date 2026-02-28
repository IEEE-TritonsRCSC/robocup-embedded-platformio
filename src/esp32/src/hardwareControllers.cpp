#include "hardwareControllers.h"
#include <Arduino.h>
#include "global_vars.h"
#include "helpers.h"
#include "credentials.h"
#include "WiFi.h"

void blink(int led, int count, int interval)
{
    for (int i = 0; i < count * interval; i += interval)
    {
        digitalWrite(led, HIGH);
        delay(interval);
        digitalWrite(led, LOW);
        delay(interval);
    }
}

void turnLEDOn(int led) {
    digitalWrite(led, HIGH);
}

void turnLEDOff(int led) {
    digitalWrite(led, LOW);
}

void initializeAndBlinkLED(int led, int count, int interval) {
    pinMode(led, OUTPUT);
    blink(led, count, interval);
}

void setDribbler(bool on, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    motor_command[DRIBBLER_MOTOR_INDEX] = on ? DRIBBLER_ON : DRIBBLER_OFF;
}

void prepare_and_send_motor_command(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command)
{
    translateVelUandVelVIntoWheelVelocities(wheel_velocities, robotVelocity);

    PRINT("(");
    for (int wheel_i = 0; wheel_i < NUM_WHEELS; wheel_i++) {

        translateWheelVelocitiesIntoAngular(wheel_velocities,wheel_i);

        addAngularVelocitiesToWheelVelocities(wheel_velocities, robotVelocity, wheel_i);

        // Convert wheel rad/s -> motor rpm
        float wheel_rpm = wheel_velocities[wheel_i] * RADS_TO_RPM;
        float motor_rpm = wheel_rpm * MOTOR_REDUCTION_RATIO;

        int speed = static_cast<int>(roundf(motor_rpm));
        speed = clamp_int(speed, static_cast<int>(INT16_MIN), static_cast<int>(INT16_MAX));

        int index = MOTOR_CMD_HEADER_SIZE + (wheel_i * 2);

        motor_command[index] = (speed >> 8 & 0xFF);
        motor_command[index + 1] = (speed & 0xFF);
        PRINT(speed, " ");
    }

    sendMotorCommand(robotVelocity, motor_command);

    if (stop_dribbler_on_next_command)
    {
        setDribbler(false, motor_command);
        stop_dribbler_on_next_command = false;
    }

    decayVelUandVelV(robotVelocity);
}

void connect_wifi() {
    printWiFiConnectingMessage();
    const int attemptWaitInterval = 500;
    beginWiFiAndWait(attemptWaitInterval);
    printWiFiConnectedMessage();
}

void beginWiFiAndWait(int waitInterval) {
    WiFi.begin(SSID, PASSWORD);
    waitUntilWiFiConnected(waitInterval);
}

void printWiFiConnectingMessage() {
    PRINT("\nConnecting WiFi to ", SSID);
}
void printWiFiConnectedMessage() {
    PRINT("\nWiFi connected", "\nIP address: ", WiFi.localIP(), "\n");
}

void waitUntilWiFiConnected(int waitInterval) {
    while (WiFi.status() != WL_CONNECTED) {
        delay(waitInterval);
        PRINT(".");
    }
}

void init_motor_command(std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, std::array<uint8_t, MOTOR_CMD_HEADER_SIZE> motor_cmd_headers)
{
    for (int index = 0; index < MOTOR_COMMAND_SIZE; index++)
    {
        if (index < MOTOR_CMD_HEADER_SIZE)
        {
            motor_command[index] = motor_cmd_headers[index];
        }
        else
        {
            motor_command[index] = 0;
        }
    }
}

void sendMotorCommand(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command) {
    PRINT(static_cast<int>(motor_command[DRIBBLER_MOTOR_INDEX]), ") | ");
    PRINT("(", robotVelocity.vel_u, " ", robotVelocity.vel_v, " ", robotVelocity.vel_w, ")\n");
    robotSerial.write(motor_command.data(), motor_command.size());
}

void translateVelUandVelVIntoWheelVelocities(float wheel_velocities[4], RobotVelocity& robotVelocity) {
    wheel_velocities[0] = (robotVelocity.vel_u * -sinFront) + (robotVelocity.vel_v * -cosFront); // front-right
    wheel_velocities[1] = (robotVelocity.vel_u * sinBack) + (robotVelocity.vel_v * -cosBack);    // back-right
    wheel_velocities[2] = (robotVelocity.vel_u * sinBack) + (robotVelocity.vel_v * cosBack);     // back-left
    wheel_velocities[3] = (robotVelocity.vel_u * -sinFront) + (robotVelocity.vel_v * cosFront);  // front-left
}

void decayVelUandVelV(RobotVelocity &robotVelocity) {
    robotVelocity.vel_u *= 0.4;
    robotVelocity.vel_v *= 0.4;
}

void translateWheelVelocitiesIntoAngular(float wheel_velocities[4], int wheelIndex) {
    wheel_velocities[wheelIndex] = wheel_velocities[wheelIndex] / rad_wheel;
}

void addAngularVelocitiesToWheelVelocities(float wheel_velocities[4], RobotVelocity &robotVelocity, int wheelIndex) {
    wheel_velocities[wheelIndex] += robotVelocity.vel_w * rad_robot / rad_wheel;
}