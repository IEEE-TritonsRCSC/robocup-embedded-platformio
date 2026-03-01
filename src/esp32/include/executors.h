#pragma once

#include "RobotVelocity.h"
#include "global_consts.h"
#include "KickerState.h"
#include "HardwareSerial.h"

/**
 * Executes a stop command and prepares the motor command buffer.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 * @param robotSerial Serial interface used to send commands.
 * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
 */
void execute_stop(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command);
/**
 * Updates the robot velocity to perform a turn.
 * @param angular_speed Desired angular speed.
 * @param robotVelocity Robot velocity state to update.
 */
void execute_turn(float angular_speed, RobotVelocity &robotVelocity);
/**
 * Updates the robot velocity to perform a dash.
 * @param power Dash power.
 * @param dir Dash direction.
 * @param robotVelocity Robot velocity state to update.
 */
void execute_dash(float power, float dir, RobotVelocity &robotVelocity);
/**
 * Executes a soft kick command and updates buffers/state as needed.
 * @param power Kick power.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
 */
void execute_skick(float power, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, bool &stop_dribbler_on_next_command);
/**
 * Executes a kick command and updates the kicker state.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 * @param kicker_state Kicker state to update.
 */
void execute_kick(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state);
/**
 * Executes a catch command and prepares the motor command buffer.
 * @param robotVelocity Robot velocity state to update.
 * @param motor_command Motor command buffer to populate.
 */
void execute_catch(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command);
