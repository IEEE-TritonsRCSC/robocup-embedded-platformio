#include "parsers.h"
#include "global_vars.h"
#include "executors.h"
#include "hardwareControllers.h"

void handleNewChar(char c, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer)
{
    // Each line or "string" received is a message
    if (c == '\n' || c == '\0')
    {
        commsBuffer.buffer[packet_info.numBytes] = '\0'; // null terminate the string
        if (packet_info.numBytes)
        {                     // if buffer not empty
            parseMsg(commsBuffer.buffer, robotVelocity, motor_command, kicker_state, robotSerial, stop_dribbler_on_next_command, current_cmd, wheel_velocities, commsBuffer); // process the message
            commsBuffer.buffer[0] = '\0'; // reset buffer
            packet_info.numBytes = 0;         // reset numBytes
        }
    }
    else
    {
        commsBuffer.buffer[packet_info.numBytes] = c; // add char to buffer
        if (++packet_info.numBytes == MAX_BUFFER_SIZE - 1)
        {                        // prevent overflow
            handleNewChar('\0', robotVelocity, motor_command, kicker_state, robotSerial, stop_dribbler_on_next_command, current_cmd, wheel_velocities, commsBuffer); // force terminate the string
        }
    }
}

void parseMsg(char *msg, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer)
{
    if (strcmp(msg, "stop") == 0)
    {
        execute_stop(robotVelocity, motor_command, robotSerial, stop_dribbler_on_next_command, wheel_velocities);
    }
    else if (sscanf(msg, RELEVANT_FORMAT, &commsBuffer.cmd_buffer, &packet_info.bytesParsed) == 1)
    {
        msg += packet_info.bytesParsed;
        parseCommand(commsBuffer.cmd_buffer, msg, robotVelocity, motor_command, kicker_state, robotSerial,stop_dribbler_on_next_command, current_cmd, wheel_velocities, commsBuffer);
    }
    commsBuffer.cmd_buffer[0] = '\0';
}

void parseCommand(char *command, char *parameters, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer)
{
    switch (command[0])
    {
    case 't': // turn
        if (sscanf(parameters, " %f", &current_cmd.angular_speed) == 1)
        {
            execute_turn(current_cmd.angular_speed, robotVelocity);
            break;
        }
        return;
    case 'd': // dash
        if (sscanf(parameters, " %f %f", &current_cmd.power, &current_cmd.dir) == 2)
        {
            execute_dash(current_cmd.power, current_cmd.dir, robotVelocity);
            break;
        }
        return;
    case 's': // skick
        if (sscanf(parameters, " %f", &current_cmd.power) == 1)
        {
            execute_skick(current_cmd.power, robotVelocity, motor_command, stop_dribbler_on_next_command);
            break;
        }
        return;
    case 'k': // kick
        execute_kick(robotVelocity, motor_command, kicker_state);
        break;
    case 'c': // catch
        execute_catch(robotVelocity, motor_command);
        break;
    default:
        return;
    }
    prepare_and_send_motor_command(robotVelocity, motor_command, robotSerial, stop_dribbler_on_next_command, wheel_velocities);
    Serial.println(micros() - packet_info.packet_time);
}
