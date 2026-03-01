#pragma once

#include "stdint.h"
#include <Arduino.h>
#include "WiFi.h"
#include "RobotVelocity.h"
#include "global_consts.h"
#include "KickerState.h"
#include "HardwareSerial.h"
#include "MotionCommand.h"
#include "CommsBuffer.h"

class PacketInfo {
    public:
    uint16_t packet_size;
    uint16_t last_packet_size;
    unsigned long packet_time;
    int numBytes;
    int bytesParsed;

    /**
     * Initializes packet tracking state.
     */
    PacketInfo() : packet_size(0), last_packet_size(0), packet_time(0), numBytes(0), bytesParsed(0) {}
    /**
     * Checks whether a packet is currently available.
     * @return True if a packet is available, otherwise false.
     */
    bool isPacketAvailable();
    /**
     * Checks whether the last packet is available.
     * @return True if the last packet is available, otherwise false.
     */
    bool isLastPacketAvailable();
    /**
     * Updates the stored last packet size.
     */
    void updateLastPacketSize();
    /**
     * Updates the current packet size from the UDP interface.
     * @param udp UDP interface to query.
     */
    void updatePacketSize(WiFiUDP &udp);
    /**
     * Resets the last packet size to zero.
     */
    void resetLastPacketSize();
    /**
     * Updates the packet timestamp.
     */
    void updatePacketTime();
    /**
     * Prints the last packet size.
     */
    void printLastPacketSize();

    // The network may have multiple UDP packets queue up in the buffer
    // Read all of them, but only process the last one to reduce jitter
    /**
     * Reads all queued packets, keeping only the last one for processing.
     * @param udp UDP interface to read from.
     * @param commsBuffer Communication buffers to store packet data.
     */
    void readAllPackets(WiFiUDP &udp, CommsBuffer &commsBuffer);
    /**
     * Updates packet size and reads all queued packets.
     * @param udp UDP interface to read from.
     * @param commsBuffer Communication buffers to store packet data.
     */
    void updatePacketSizeAndReadAllPackets(WiFiUDP &udp, CommsBuffer &commsBuffer);
    /**
     * Processes the last received packet and updates robot state and outputs.
     * @param robotVelocity Robot velocity state to update.
     * @param motor_command Motor command buffer to populate.
     * @param kicker_state Kicker state to update.
     * @param robotSerial Serial interface used to send commands.
     * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
     * @param current_cmd Current motion command to update.
     * @param wheel_velocities Wheel velocity array to update.
     * @param commsBuffer Communication buffers containing packet data.
     */
    void processLastPacket(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer);
    /**
     * Updates packet size, reads all queued packets, and processes the last one.
     * @param udp UDP interface to read from.
     * @param robotVelocity Robot velocity state to update.
     * @param motor_command Motor command buffer to populate.
     * @param kicker_state Kicker state to update.
     * @param robotSerial Serial interface used to send commands.
     * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
     * @param current_cmd Current motion command to update.
     * @param wheel_velocities Wheel velocity array to update.
     * @param commsBuffer Communication buffers containing packet data.
     */
    void updatePacketSizeAndReadAllPacketsAndProcessLastPacket(WiFiUDP &udp, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer);
    /**
     * Updates packet sizes, reads all queued packets, and processes the last one.
     * @param udp UDP interface to read from.
     * @param robotVelocity Robot velocity state to update.
     * @param motor_command Motor command buffer to populate.
     * @param kicker_state Kicker state to update.
     * @param robotSerial Serial interface used to send commands.
     * @param stop_dribbler_on_next_command Flag indicating whether to stop the dribbler on the next command.
     * @param current_cmd Current motion command to update.
     * @param wheel_velocities Wheel velocity array to update.
     * @param commsBuffer Communication buffers containing packet data.
     */
    void updatePacketSizesAndReadAllPacketsAndProcessLastPacket(WiFiUDP &udp, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state, HardwareSerial &robotSerial, bool &stop_dribbler_on_next_command, MotionCommand &current_cmd, float wheel_velocities[4], CommsBuffer &commsBuffer);
};
