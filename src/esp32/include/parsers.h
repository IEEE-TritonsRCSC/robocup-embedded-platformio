#pragma once

#include "RobotVelocity.h"
#include "KickerState.h"
#include "HardwareSerial.h"
#include "global_consts.h"
#include "MotionCommand.h"
#include "CommsBuffer.h"
#include "PacketInfo.h"

#define RELEVANT_FORMAT ROBOT_NO " %s %n"
#define ROBOT_NO "1"

/**
 * Handles a newly received character in the command stream.
 * @param c Incoming character.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 * @param kicker_state Kicker state to update.
 * @param robotSerial Serial interface used to send commands.
 * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
 * @param current_cmd Current motion command to update.
 * @param wheel_velocities Wheel velocity array to update.
 * @param commsBuffer Communication buffers to update.
 * @param packet_info Packet tracking state to update.
 */
void handleNewChar(char c, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer, PacketInfo &packet_info);
/**
 * Parses a message string and updates robot state and outputs.
 * @param msg Message buffer to parse.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 * @param kicker_state Kicker state to update.
 * @param robotSerial Serial interface used to send commands.
 * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
 * @param current_cmd Current motion command to update.
 * @param wheel_velocities Wheel velocity array to update.
 * @param commsBuffer Communication buffers to update.
 * @param packet_info Packet tracking state to update.
 */
void parseMsg(char *msg, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer, PacketInfo &packet_info);
/**
 * Parses a command and parameter string and updates robot state and outputs.
 * @param command Command token to parse.
 * @param parameters Parameter string for the command.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 * @param kicker_state Kicker state to update.
 * @param robotSerial Serial interface used to send commands.
 * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
 * @param current_cmd Current motion command to update.
 * @param wheel_velocities Wheel velocity array to update.
 * @param commsBuffer Communication buffers to update.
 * @param packet_info Packet tracking state to update.
 */
void parseCommand(char *command, char *parameters, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer, PacketInfo &packet_info);
