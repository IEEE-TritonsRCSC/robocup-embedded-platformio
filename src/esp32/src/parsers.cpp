#include "parsers.h"
#include "global_vars.h"
#include "executors.h"
#include "hardwareControllers.h"

void handleNewChar(char c, RobotVelocity &robotVelocity)
{
    // Each line or "string" received is a message
    if (c == '\n' || c == '\0')
    {
        commsBuffer.buffer[packet_info.numBytes] = '\0'; // null terminate the string
        if (packet_info.numBytes)
        {                     // if buffer not empty
            parseMsg(commsBuffer.buffer, robotVelocity); // process the message
            commsBuffer.buffer[0] = '\0'; // reset buffer
            packet_info.numBytes = 0;         // reset numBytes
        }
    }
    else
    {
        commsBuffer.buffer[packet_info.numBytes] = c; // add char to buffer
        if (++packet_info.numBytes == MAX_BUFFER_SIZE - 1)
        {                        // prevent overflow
            handleNewChar('\0', robotVelocity); // force terminate the string
        }
    }
}

void parseMsg(char *msg, RobotVelocity &robotVelocity)
{
    if (strcmp(msg, "stop") == 0)
    {
        execute_stop(robotVelocity);
    }
    else if (sscanf(msg, RELEVANT_FORMAT, &commsBuffer.cmd_buffer, &packet_info.bytesParsed) == 1)
    {
        msg += packet_info.bytesParsed;
        parseCommand(commsBuffer.cmd_buffer, msg);
    }
    commsBuffer.cmd_buffer[0] = '\0';
}

void parseCommand(char *command, char *parameters)
{
    switch (command[0])
    {
    case 't': // turn
        if (sscanf(parameters, " %f", &current_cmd.angular_speed) == 1)
        {
            execute_turn(current_cmd.angular_speed);
            break;
        }
        return;
    case 'd': // dash
        if (sscanf(parameters, " %f %f", &current_cmd.power, &current_cmd.dir) == 2)
        {
            execute_dash(current_cmd.power, current_cmd.dir);
            break;
        }
        return;
    case 's': // skick
        if (sscanf(parameters, " %f", &current_cmd.power) == 1)
        {
            execute_skick(current_cmd.power);
            break;
        }
        return;
    case 'k': // kick
        execute_kick();
        break;
    case 'c': // catch
        execute_catch();
        break;
    default:
        return;
    }
    prepare_and_send_motor_command();
    Serial.println(micros() - packet_info.packet_time);
}
